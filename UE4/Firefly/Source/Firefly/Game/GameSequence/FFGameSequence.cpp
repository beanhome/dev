// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence.h"
#include "UnrealNetwork.h"
#include "VisualLogger.h"
#include "Game/FireflyPlayerController.h"

AFFGameSequence::AFFGameSequence()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	State = EFFClientGameSeqState::None;
}

void AFFGameSequence::Log(const FString& str) const
{
	FString tab = "";
	for (int32 i = 0; i < GetMyPlayerId()+1; ++i)
		tab += "\t\t\t\t";
	FString mode = GetMultiMode();
	FString player = (GetMyPlayerId() != -1 ? FString::Printf(TEXT("%d"), GetMyPlayerId()) : TEXT(""));

	FString classname = GetClass()->GetName();
	int32 i = str.Find("::");
	FString funcname = (i != -1 ? str.RightChop(i+2) : str);

	UE_LOG(FFSeq, Log, TEXT("%s %s %s %s :: %s"), *tab, *mode, *player, *classname, *funcname);

	UE_VLOG(this, FFSeq, Log, TEXT("%s %s %s :: %s"), *mode, *player, *classname, *funcname);
}

void AFFGameSequence::PostActorCreated()
{
	SEQLOG();

	if (GetWorld())
	{
		if (IsServer())
		{
			for (TActorIterator<AFireflyPlayerController> It(GetWorld()); It; ++It)
			{
				AFireflyPlayerController* PlayerController = *It;

				ClientState.Add(PlayerController->GetId(), EFFClientGameSeqState::None);
			}
		}
		else if (IsClient())
		{
			ensure(Role != ROLE_Authority);

			SetState(EFFClientGameSeqState::Spawned);
		}
	}
}

void AFFGameSequence::Destroyed()
{
	SEQLOG();

	Super::Destroyed();
}

bool AFFGameSequence::IsCameraFree() const
{
	if (State == EFFClientGameSeqState::Ended)
		return true;

	for (AFFGameSequence* Sequence : SubSequences)
	{
		ensure(Sequence != nullptr);

		if (Sequence != nullptr && Sequence->IsCameraFree() == false)
			return false;
	}

	return true;
}

bool AFFGameSequence::IsActorInteractive() const
{
	for (AFFGameSequence* Sequence : SubSequences)
	{
		//ensure(Sequence != nullptr);

		if (Sequence != nullptr && Sequence->IsActorInteractive() == false)
			return false;
	}

	return true;
}



bool AFFGameSequence::IsServer() const
{
	return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() != nullptr);
}

bool AFFGameSequence::IsClient() const
{
	//AFireflyPlayerController* Player = GetFFPlayerController();
	//return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Player != nullptr && Player->Role != ROLE_Authority);

	return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Role != ROLE_Authority);

}

bool AFFGameSequence::IsLocal() const
{
	//AFireflyPlayerController* Player = GetFFPlayerController();
	//return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Player != nullptr && Player->Role == ROLE_Authority);

	return (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr && Role == ROLE_Authority);
}

FString AFFGameSequence::GetMultiMode() const
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


bool AFFGameSequence::IsSupportedForNetworking() const
{
	return true;
}

void AFFGameSequence::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence, SubSequences);
}

AFireflyPlayerController* AFFGameSequence::GetFFPlayerController() const
{
	UGameInstance* GameInstance = (GetWorld() != nullptr ? GetWorld()->GetGameInstance() : nullptr);
	return (GameInstance != nullptr ? Cast<AFireflyPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);
}

int32 AFFGameSequence::GetMyPlayerId() const
{
	AFireflyPlayerController* Player = GetFFPlayerController();
	return (Player != nullptr ? Player->GetId() : -1);
}

bool AFFGameSequence::IsUnderCamera(const FString& CameraName) const
{
	if (CameraName.IsEmpty())
		return true;

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (PlayerController == nullptr || PlayerController->GetCurrentCamera() == nullptr)
		return false;

	FString CurrentCamera = PlayerController->GetCurrentCamera()->GetName();

	return (CurrentCamera == CameraName);
}

void AFFGameSequence::ServerInit(AFFGameSequence* OwnerSequence)
{
	check(IsServer());

	SEQLOG();

	SetOwner(OwnerSequence);
	ClientInit(OwnerSequence);
}

void AFFGameSequence::ServerStart()
{
	check(IsServer());

	SEQLOG();

	ClientStart();
}

void AFFGameSequence::ServerEnd()
{
	check(IsServer());

	if (State < EFFClientGameSeqState::Ended)
	{
		SEQLOG();
		ClientEnd();
	}
}

void AFFGameSequence::Init(AFFGameSequence* OwnerSequence)
{
	SEQLOG();

	if (OwnerSequence)
		SetOwner(OwnerSequence);
}

void AFFGameSequence::Start()
{
	SEQLOG();
}

void AFFGameSequence::End()
{
	SEQLOG();
}

void AFFGameSequence::SetState(EFFClientGameSeqState NewState)
{
	check(IsClient());
	ensure(Role != ROLE_Authority);

	SEQLOG();

	State = NewState;

	AFireflyPlayerController* PlayerController = GetFFPlayerController();
	PlayerController->SendClientStateToServer(this, State);
}

void AFFGameSequence::ServerReceiveClientState(int32 id, EFFClientGameSeqState NewState)
{
	check(IsServer());

	SEQLOG();

	ClientState[id] = NewState;

	for (TPair<int32, EFFClientGameSeqState>& _State : ClientState)
	{
		if (_State.Value != NewState)
			return;
	}

	State = NewState;
	ServerOnAllClientSynchro(State);
}

/*
void AFFGameSequence::ServerReceiveMouseEnterActor(int32 PlayerId, class AFFActor* Actor)
{
}

void AFFGameSequence::ServerReceiveMouseExitActor(int32 PlayerId, class AFFActor* Actor)
{
}

void AFFGameSequence::ServerReceiveMouseClickActor(int32 PlayerId, class AFFActor* Actor)
{
}
*/

void AFFGameSequence::ServerOnAllClientSynchro(EFFClientGameSeqState NewState)
{
	check(IsServer());

	SEQLOG();

	switch (NewState)
	{
		case EFFClientGameSeqState::None:
			break;

		case EFFClientGameSeqState::Spawned:
			ServerInit(GetOwner<AFFGameSequence>());
			break;

		case EFFClientGameSeqState::Initialized:
			ServerStart();
			break;

		case EFFClientGameSeqState::Started:
			break;

		case EFFClientGameSeqState::Ended:
			EndDelegate.Broadcast(this);
			GetOwner<AFFGameSequence>()->OnSubSequenceEnded(this);
			Destroy();
			break;
	}
}

void AFFGameSequence::SendResponseToServer(int32 res)
{
	check(IsClient());
	ensure(Role != ROLE_Authority);

	GetFFPlayerController()->SendClientResponseToServer(this, res);
}

	
void AFFGameSequence::ServerReceiveResponse(int32 res)
{
	check(IsServer());

	SEQLOG();
}

void AFFGameSequence::ServerStopCurrentSequence()
{
	check(IsServer());

	SEQLOG();

	//ensure(SubSequences.Num() == 0);
	for (AFFGameSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);
		ensure(Sequence->State == EFFClientGameSeqState::Ended);
		if (Sequence->State != EFFClientGameSeqState::Ended)
			Sequence->ServerStopCurrentSequence();
	}

	ServerEnd();

	GetOwner<AFFGameSequence>()->OnSubSequenceStopped(this);
}

AFFGameSequence* AFFGameSequence::FindSubSequence(UClass* Class) const
{
	for (AFFGameSequence* Sub : SubSequences)
	{
		if (Sub != nullptr && Sub->IsA(Class))
			return Sub;
	}

	for (const AFFGameSequence* Sub : SubSequences)
	{
		if (Sub != nullptr)
		{
			AFFGameSequence* Found = Sub->FindSubSequence(Class);
			if (Found != nullptr)
				return Found;
		}
	}

	return nullptr;
}


AFFGameSequence* AFFGameSequence::StartSubSequence(UClass* Class)
{
	check(IsServer());

	SEQLOG();

	FActorSpawnParameters Param;
	Param.Owner = this;
	AFFGameSequence* SubSequence = CastChecked<AFFGameSequence>(GetWorld()->SpawnActor(Class, nullptr, nullptr, Param));
	SubSequences.Add(SubSequence);

	return SubSequence;
}

void AFFGameSequence::StopSubSequence(AFFGameSequence* SubSequence)
{
	check(IsServer());

	SEQLOG();

	SubSequence->ServerEnd();
	SubSequences.Remove(SubSequence);
}

void AFFGameSequence::StopLocalSubSequence(AFFGameSequence* SubSequence)
{
	check(IsClient() || IsLocal());

	SEQLOG();

	SubSequence->End();
	SubSequences.Remove(SubSequence);
	SubSequence->Destroy();
}

void AFFGameSequence::OnSubSequenceStopped(AFFGameSequence* SubSequence)
{
	check(IsServer());

	SEQLOG();
}

void AFFGameSequence::OnSubSequenceEnded(AFFGameSequence* SubSequence)
{
	check(IsServer());

	SEQLOG();

	SubSequences.Remove(SubSequence);
}


bool AFFGameSequence::PropagateMouseEnterActor(int32 PlayerId, class AFFActor* Actor)
{
	//check(IsClient() || IsLocal());

	for (AFFGameSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->PropagateMouseEnterActor(PlayerId, Actor))
			return true;
	}

	return OnMouseEnterActor(PlayerId, Actor);
}

bool AFFGameSequence::PropagateMouseLeaveActor(int32 PlayerId, class AFFActor* Actor)
{
	//check(IsClient() || IsLocal());

	for (AFFGameSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->PropagateMouseLeaveActor(PlayerId, Actor))
			return true;
	}

	return OnMouseLeaveActor(PlayerId, Actor);
}

bool AFFGameSequence::PropagateMouseClickActor(int32 PlayerId, class AFFActor* Actor)
{
	//check(IsClient() || IsLocal());

	for (AFFGameSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->PropagateMouseClickActor(PlayerId, Actor))
			return true;
	}

	return OnMouseClickActor(PlayerId, Actor);
}

bool AFFGameSequence::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}

bool AFFGameSequence::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}

bool AFFGameSequence::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}

void AFFGameSequence::ClientInit_Implementation(AFFGameSequence* OwnerSequence)
{
	Init(OwnerSequence);
	if (IsClient())
	{
		ensure(Role != ROLE_Authority);
		SetState(EFFClientGameSeqState::Initialized);
	}
}

void AFFGameSequence::ClientStart_Implementation()
{
	Start();
	if (IsClient())
	{
		ensure(Role != ROLE_Authority);
		SetState(EFFClientGameSeqState::Started);
	}
}

void AFFGameSequence::ClientEnd_Implementation()
{
	End();
	if (IsClient())
	{
		ensure(Role != ROLE_Authority);
		SetState(EFFClientGameSeqState::Ended);
	}
}

void AFFGameSequence::DrawDebug(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColor::White);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("%s"), *GetClass()->GetName()), x, y);

	x += 5.f;
	DrawDebugSpecific(Canvas, x, y);
	x -= 5.f;

	x += 15.f;
	for (AFFGameSequence* Sequence : SubSequences)
	{
		if (Sequence)
			Sequence->DrawDebug(Canvas, x, y);
	}
	x -= 15.f;
}

void AFFGameSequence::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{

}
