// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GameSequence.h"
#include "GSSequence.h"
#include "UnrealNetwork.h"
#include "VisualLogger.h"
#include "GSPlayerController.h"
#include "EngineUtils.h"

AGSSequence::AGSSequence()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	State = EGSClientState::None;
	PrimaryActorTick.bCanEverTick = true;
}

void AGSSequence::Log(const FString& str) const
{
	FString tab = "";
	for (int32 i = 0; i < GetMyPlayerId()+1; ++i)
		tab += "\t\t\t\t";
	FString mode = GetMultiMode();
	FString player = (GetMyPlayerId() != -1 ? FString::Printf(TEXT("%d"), GetMyPlayerId()) : TEXT(""));

	FString classname = GetClass()->GetName();
	int32 i = str.Find("::");
	FString funcname = (i != -1 ? str.RightChop(i+2) : str);

	UE_LOG(GameSequence, Log, TEXT("%s %s %s %s :: %s"), *tab, *mode, *player, *classname, *funcname);

	UE_VLOG(this, GameSequence, Log, TEXT("%s %s %s :: %s"), *mode, *player, *classname, *funcname);
}

void AGSSequence::PostActorCreated()
{
	SEQLOG();

	if (GetWorld())
	{
		if (IsServer())
		{
			for (TActorIterator<AGSPlayerController> It(GetWorld()); It; ++It)
			{
				AGSPlayerController* PlayerController = *It;

				ClientState.Add(PlayerController->GetId(), EGSClientState::None);
			}
		}
		else if (IsClient())
		{
			ensure(Role != ROLE_Authority);

			SetState(EGSClientState::Spawned);
		}
	}
}

void AGSSequence::Destroyed()
{
	SEQLOG();

	for (FGSSequenceDefinition& Def : SubSeqDefinitions)
	{
		if (Def.Param != nullptr)
			delete Def.Param;
	}

	Super::Destroyed();

	if (InitParameter != nullptr)
		delete InitParameter;
}

bool AGSSequence::IsActorInteractive() const
{
	for (AGSSequence* Sequence : SubSequences)
	{
		//ensure(Sequence != nullptr);

		if (Sequence != nullptr && Sequence->IsActorInteractive() == false)
			return false;
	}

	return true;
}



bool AGSSequence::IsServer() const
{
	return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() != nullptr);
}

bool AGSSequence::IsClient() const
{
	//AGSPlayerController* Player = GetGSPlayerController();
	//return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Player != nullptr && Player->Role != ROLE_Authority);

	return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Role != ROLE_Authority);

}

bool AGSSequence::IsLocal() const
{
	//AGSPlayerController* Player = GetGSPlayerController();
	//return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Player != nullptr && Player->Role == ROLE_Authority);

	return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Role == ROLE_Authority);
}

FString AGSSequence::GetMultiMode() const
{
	if (IsServer())
		return "Server";
	else if (IsClient())
		return "Client";
	else if (IsLocal())
		return "Local";
	else
		return "Error";
}


bool AGSSequence::IsSupportedForNetworking() const
{
	return true;
}

void AGSSequence::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGSSequence, SubSequences);
}

AGSPlayerController* AGSSequence::GetGSPlayerController() const
{
	UGameInstance* GameInstance = (GetWorld() != nullptr ? GetWorld()->GetGameInstance() : nullptr);
	return (GameInstance != nullptr ? Cast<AGSPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);
}

int32 AGSSequence::GetMyPlayerId() const
{
	AGSPlayerController* Player = GetGSPlayerController();
	return (Player != nullptr ? Player->GetId() : -1);
}

void AGSSequence::ServerInit(AGSSequence* OwnerSequence)
{
	check(IsServer());

	SEQLOG();

	SetOwner(OwnerSequence);
	ClientInit(OwnerSequence);
}

void AGSSequence::ServerStart()
{
	check(IsServer());

	SEQLOG();

	ClientStart();
}

void AGSSequence::ServerEnd()
{
	check(IsServer());

	if (State < EGSClientState::Ended)
	{
		SEQLOG();
		ClientEnd();
	}
}

void AGSSequence::ServerSuspend()
{
	check(IsServer());

	SEQLOG();

	ClientSuspend();
}

void AGSSequence::ServerResume()
{
	check(IsServer());

	SEQLOG();

	ClientResume();
}

void AGSSequence::Init(AGSSequence* OwnerSequence)
{
	SEQLOG();

	if (OwnerSequence)
		SetOwner(OwnerSequence);
}

void AGSSequence::Start()
{
	SEQLOG();
}

void AGSSequence::End()
{
	SEQLOG();
}

void AGSSequence::Suspend()
{
	SEQLOG();
}

void AGSSequence::Resume()
{
	SEQLOG();
}

void AGSSequence::SetState(EGSClientState NewState)
{
	check(IsClient());
	ensure(Role != ROLE_Authority);

	SEQLOG();

	State = NewState;

	AGSPlayerController* PlayerController = GetGSPlayerController();
	PlayerController->SendClientStateToServer(this, State);
}

void AGSSequence::ServerReceiveClientState(int32 id, EGSClientState NewState)
{
	check(IsServer());

	SEQLOG();

	if (ClientState.Find(id) == nullptr)
		ClientState.Add(id, EGSClientState::None);

	ClientState[id] = NewState;

	for (TPair<int32, EGSClientState>& _State : ClientState)
	{
		if (_State.Value != NewState)
			return;
	}

	State = NewState;
	ServerOnAllClientSynchro(State);
}

void AGSSequence::ServerOnAllClientSynchro(EGSClientState NewState)
{
	check(IsServer());

	SEQLOG();

	switch (NewState)
	{
		case EGSClientState::None:
			break;

		case EGSClientState::Spawned:
			ServerInit(GetOwner<AGSSequence>());
			break;

		case EGSClientState::Initialized:
			ServerStart();
			break;

		case EGSClientState::Started:
			break;

		case EGSClientState::Ended:
			if (EndDelegate.IsBound())
				EndDelegate.Execute(this);
			GetOwner<AGSSequence>()->OnSubSequenceEnded(this); // Call after EndDelegate.Broadcast to let push an other sequence (Resume or not)
			Destroy();
			break;
	}
}

void AGSSequence::SendResponseToServer(FGSResponse res)
{
	check(IsClient());
	ensure(Role != ROLE_Authority);

	GetGSPlayerController()->SendClientResponseToServer(this, res);
}


void AGSSequence::ClientStopSequence()
{
	check(IsClient());
	ensure(Role != ROLE_Authority);

	GetGSPlayerController()->SendClientStopSequenceToServer(this);
}
	
void AGSSequence::ServerReceiveResponse(FGSResponse res)
{
	check(IsServer());

	SEQLOG();
}

void AGSSequence::ServerStopCurrentSequence()
{
	check(IsServer());

	SEQLOG();

	//ensure(SubSequences.Num() == 0);
	for (AGSSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);
		ensure(Sequence->State == EGSClientState::Ended);
		if (Sequence->State != EGSClientState::Ended)
			Sequence->ServerStopCurrentSequence();
	}

	ServerEnd();
}

AGSSequence* AGSSequence::FindSubSequence(UClass* Class) const
{
	for (AGSSequence* Sub : SubSequences)
	{
		if (Sub != nullptr && Sub->IsA(Class))
			return Sub;
	}

	for (const AGSSequence* Sub : SubSequences)
	{
		if (Sub != nullptr)
		{
			AGSSequence* Found = Sub->FindSubSequence(Class);
			if (Found != nullptr)
				return Found;
		}
	}

	return nullptr;
}


AGSSequence* AGSSequence::StartSubSequence(UClass* Class, FGSSequenceInit* Param)
{
	check(IsServer());

	SEQLOG();

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	AGSSequence* SubSequence = CastChecked<AGSSequence>(GetWorld()->SpawnActor(Class, nullptr, nullptr, SpawnParam));
	SubSequence->InitParameter = Param;
	SubSequences.Add(SubSequence);

	if (SubSequences.Num() == 1)
		ServerSuspend();

	return SubSequence;
}

void AGSSequence::StopSubSequence(AGSSequence* SubSequence)
{
	check(IsServer());

	SEQLOG();

	SubSequence->ServerEnd();
	SubSequences.Remove(SubSequence);

	if (SubSequences.Num() == 0)
		ServerResume();
}

void AGSSequence::LocalStopCurrentSequence()
{
	End();

	if (EndDelegate.IsBound())
		EndDelegate.Execute(this);

	GetOwner<AGSSequence>()->OnSubSequenceEnded(this); // Call after EndDelegate.Broadcast to let push an other sequence (Resume or not)

	Destroy();
}

void AGSSequence::StopLocalSubSequence(AGSSequence* SubSequence)
{
	check(IsClient() || IsLocal());

	SEQLOG();

	SubSequence->End();
	SubSequences.Remove(SubSequence);
	SubSequence->Destroy();

	if (SubSequences.Num() == 0)
		Resume();
}

void AGSSequence::OnSubSequenceEnded(AGSSequence* SubSequence)
{
	SEQLOG();

	SubSequences.Remove(SubSequence);

	if (SubSequences.Num() == 0)
	{
		if (IsServer())
			ServerResume();
		else
			Resume();
	}
}

void AGSSequence::AddSubSequence(UClass* Class, FGSSequenceInit* Param)
{
	AddSubSequence_Intern(Class, Param);
}

FGSSequenceDefinition& AGSSequence::AddSubSequence_Intern(UClass* Class, FGSSequenceInit* Param)
{
	FGSSequenceDefinition Def;
	Def.Class = Class;
	Def.Param = Param;
	SubSeqDefinitions.Add(Def);
	return SubSeqDefinitions[SubSeqDefinitions.Num() - 1];
}

void AGSSequence::StartAllSubSequence()
{
	CurrentSubDef = 0;
	StartSubSequence(CurrentSubDef);
}

void AGSSequence::StopAutoAfterAllSubSequence(bool bEnable)
{
	bStopAutoAfterAllSubSequence = bEnable;
}


void AGSSequence::StartSubSequence(int32 id)
{
	if (id >=0 && id < SubSeqDefinitions.Num())
	{
		FGSSequenceDefinition& Def = SubSeqDefinitions[id];

		AGSSequence* Seq = StartSubSequence(Def.Class, Def.Param);
		if (Seq != nullptr)
		{
			Seq->EndDelegate.BindUObject(this, &AGSSequence::CurrentSubSequenceFinish);
			Def.Param = nullptr;
		}
	}
}

void AGSSequence::CurrentSubSequenceFinish(AGSSequence* Seq)
{
	FGSSequenceDefinition& Def = SubSeqDefinitions[CurrentSubDef];

	if (Def.EndCallBack.IsBound())
	{
		bool res = Def.EndCallBack.Execute(Seq);
		if (!res)
			return;
	}

	CurrentSubDef++;

	if (CurrentSubDef < SubSeqDefinitions.Num())
	{
		StartSubSequence(CurrentSubDef);
	}
	else if (bStopAutoAfterAllSubSequence)
	{
		ServerStopCurrentSequence();
	}
}

bool AGSSequence::PropagateMouseEnterActor(int32 PlayerId, class AGSActor* Actor)
{
	//check(IsClient() || IsLocal());

	for (AGSSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->PropagateMouseEnterActor(PlayerId, Actor))
			return true;
	}

	return OnMouseEnterActor(PlayerId, Actor);
}

bool AGSSequence::PropagateMouseLeaveActor(int32 PlayerId, class AGSActor* Actor)
{
	//check(IsClient() || IsLocal());

	for (AGSSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->PropagateMouseLeaveActor(PlayerId, Actor))
			return true;
	}

	return OnMouseLeaveActor(PlayerId, Actor);
}

bool AGSSequence::PropagateMouseClickActor(int32 PlayerId, class AGSActor* Actor)
{
	//check(IsClient() || IsLocal());

	for (AGSSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->PropagateMouseClickActor(PlayerId, Actor))
			return true;
	}

	return OnMouseClickActor(PlayerId, Actor);
}

bool AGSSequence::OnMouseEnterActor(int32 PlayerId, AGSActor* Actor)
{
	return false;
}

bool AGSSequence::OnMouseLeaveActor(int32 PlayerId, AGSActor* Actor)
{
	return false;
}

bool AGSSequence::OnMouseClickActor(int32 PlayerId, AGSActor* Actor)
{
	return false;
}

void AGSSequence::ClientInit_Implementation(AGSSequence* OwnerSequence)
{
	Init(OwnerSequence);
	if (IsClient())
	{
		ensure(Role != ROLE_Authority);
		SetState(EGSClientState::Initialized);
	}
}

void AGSSequence::ClientStart_Implementation()
{
	Start();
	if (IsClient())
	{
		ensure(Role != ROLE_Authority);
		SetState(EGSClientState::Started);
	}
}

void AGSSequence::ClientEnd_Implementation()
{
	End();
	if (IsClient())
	{
		ensure(Role != ROLE_Authority);
		SetState(EGSClientState::Ended);
	}
}

void AGSSequence::ClientSuspend_Implementation()
{
	Suspend();
}

void AGSSequence::ClientResume_Implementation()
{
	Resume();
}


void AGSSequence::DrawDebug(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColor::White);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("%s"), *GetClass()->GetName()), x, y);

	x += 5.f;
	DrawDebugSpecific(Canvas, x, y);
	x -= 5.f;

	x += 15.f;
	for (AGSSequence* Sequence : SubSequences)
	{
		if (Sequence)
			Sequence->DrawDebug(Canvas, x, y);
	}
	x -= 15.f;
}

void AGSSequence::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{

}
