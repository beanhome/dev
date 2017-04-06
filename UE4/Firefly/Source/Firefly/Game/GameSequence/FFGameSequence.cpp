// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence.h"
#include "UnrealNetwork.h"
#include "Game/FireflyPlayerController.h"

AFFGameSequence::AFFGameSequence()
: SubSequence(nullptr)
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	State = EFFClientGameSeqState::None;
}

void AFFGameSequence::PostActorCreated()
{
	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s PostActorCreated %d"), *GetMultiMode(), *GetClass()->GetName(), GetPlayerId());

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
	DOREPLIFETIME(AFFGameSequence, SubSequence);
}

AFireflyPlayerController* AFFGameSequence::GetFFPlayerController() const
{
	UGameInstance* GameInstance = (GetWorld() != nullptr ? GetWorld()->GetGameInstance() : nullptr);
	return (GameInstance != nullptr ? Cast<AFireflyPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);
}

int32 AFFGameSequence::GetPlayerId() const
{
	AFireflyPlayerController* Player = GetFFPlayerController();
	return (Player != nullptr ? Player->GetId() : -1);
}


void AFFGameSequence::ServerInit(AFFGameSequence* OwnerSequence)
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerInit"), *GetMultiMode(), *GetClass()->GetName());

	SetOwner(OwnerSequence);
	ClientInit(OwnerSequence);
}

void AFFGameSequence::ServerStart()
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerStart"), *GetMultiMode(), *GetClass()->GetName());

	ClientStart();
}

void AFFGameSequence::ServerEnd()
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerEnd"), *GetMultiMode(), *GetClass()->GetName());

	ClientEnd();
}

void AFFGameSequence::Init(AFFGameSequence* OwnerSequence)
{
	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s Init %d"), *GetMultiMode(), *GetClass()->GetName(), GetPlayerId());

	if (OwnerSequence)
		SetOwner(OwnerSequence);
}

void AFFGameSequence::Start()
{
	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s Start %d"), *GetMultiMode(), *GetClass()->GetName(), GetPlayerId());
}

void AFFGameSequence::End()
{
	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s End %d"), *GetMultiMode(), *GetClass()->GetName(), GetPlayerId());
}

void AFFGameSequence::SetState(EFFClientGameSeqState NewState)
{
	check(IsClient());
	ensure(Role != ROLE_Authority);

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s SetState %d %s"), *GetMultiMode(), *GetClass()->GetName(), GetPlayerId(), *EnumToString(EFFClientGameSeqState, NewState));

	State = NewState;

	AFireflyPlayerController* PlayerController = GetFFPlayerController();
	PlayerController->SendClientStateToServer(this, State);
}

void AFFGameSequence::ServerReceiveClientState(int32 id, EFFClientGameSeqState NewState)
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerReceiveClientState %d %s"), *GetMultiMode(), *GetClass()->GetName(), id, *EnumToString(EFFClientGameSeqState, NewState));

	ClientState[id] = NewState;

	for (TPair<int32, EFFClientGameSeqState>& _State : ClientState)
	{
		if (_State.Value != NewState)
			return;
	}

	State = NewState;
	ServerOnAllClientSynchro(State);
}

void AFFGameSequence::ServerOnAllClientSynchro(EFFClientGameSeqState NewState)
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerOnAllClientSynchro %s"), *GetMultiMode(), *GetClass()->GetName(), *EnumToString(EFFClientGameSeqState, NewState));

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

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerReceiveResponse %d"), *GetClass()->GetName(), *GetMultiMode(), res);

	if (SubSequence)
		SubSequence->ServerReceiveResponse(res);
}

void AFFGameSequence::ServerStopCurrentSequence()
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s ServerStopCurrentSequence"), *GetMultiMode(), *GetClass()->GetName());

	ensure(SubSequence == nullptr);
	if (SubSequence)
		SubSequence->ServerStopCurrentSequence();

	ServerEnd();
}

AFFGameSequence* AFFGameSequence::StartSubSequence(UClass* Class)
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s StartSubSequence %s"), *GetMultiMode(), *GetClass()->GetName(), *Class->GetName());

	FActorSpawnParameters Param;
	Param.Owner = this;
	SubSequence = CastChecked<AFFGameSequence>(GetWorld()->SpawnActor(Class, nullptr, nullptr, Param));
	//SubSequence->ServerInit(this);
	//SubSequence->ServerStart();

	return SubSequence;
}

void AFFGameSequence::StopSubSequence()
{
	check(IsServer());

	UE_LOG(Firefly, Log, TEXT("AFFGameSequence %s %s StopSubSequence %s"), *GetMultiMode(), *GetClass()->GetName(), *SubSequence->GetClass()->GetName());

	SubSequence->ServerEnd();
	SubSequence = nullptr;
}

void AFFGameSequence::OnMouseEnterSector(AFFSector* Sector)
{
	check(IsClient() || IsLocal());

	MouseEnterSector.Broadcast(Sector);

	if (SubSequence)
		SubSequence->OnMouseEnterSector(Sector);
}

void AFFGameSequence::OnMouseExitSector(AFFSector* Sector)
{
	check(IsClient() || IsLocal());

	MouseExitSector.Broadcast(Sector);

	if (SubSequence)
		SubSequence->OnMouseExitSector(Sector);
}

void AFFGameSequence::OnMouseClickSector(AFFSector* Sector)
{
	check(IsClient() || IsLocal());

	MouseClickSector.Broadcast(Sector);

	if (SubSequence)
		SubSequence->OnMouseClickSector(Sector);
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
