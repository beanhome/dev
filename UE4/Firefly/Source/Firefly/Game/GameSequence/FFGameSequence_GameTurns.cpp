// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_GameTurns.h"
#include "FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"
#include "FFGameSequence_SubGame.h"
#include "FFGameSequence_ChooseInList.h"

AFFGameSequence_GameTurns::AFFGameSequence_GameTurns()
{
}

void AFFGameSequence_GameTurns::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_GameTurns, ParallelSequences);
}

void AFFGameSequence_GameTurns::Init(AFFGameSequence* OwnerSequence)
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_GameTurns::Init %s"), *GetFFPlayerController()->GetName());

	Super::Init(OwnerSequence);
}

bool AFFGameSequence_GameTurns::IsCameraFree() const
{
	return true;
}

void AFFGameSequence_GameTurns::ServerStart()
{
	Super::ServerStart();

	AFFGameSequence_Game* GameOwner = GetOwner<AFFGameSequence_Game>();
	CurrentPlayerId = GameOwner->GetPlayersOrder()[0];

	StartPlayerTurn(CurrentPlayerId);
}


void AFFGameSequence_GameTurns::Start()
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_GameTurns::Start %s"), *GetFFPlayerController()->GetName());

	Super::Start();
}

void AFFGameSequence_GameTurns::End()
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_GameTurns::End %s"), *GetFFPlayerController()->GetName());

	Super::End();
}

void AFFGameSequence_GameTurns::StartPlayerTurn_Implementation(int32 id)
{
	if (IsClient())
	{
		if (GetFFPlayerController())
			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_GameTurns::StartPlayerTurn %s"), *GetFFPlayerController()->GetName());

		AFFGameSequence_Game* GameOwner = GetOwner<AFFGameSequence_Game>();
		CurrentPlayerId = id;

		if (CurrentPlayerId == GetPlayerId())
		{
			if (GetHud())
				GetHud()->Title = TEXT("It is your turn !");
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("Other Player Turn");
		}
	}
}

/*
void AFFGameSequence_GameTurns::FinishPlayerGameTurns_Implementation(int32 id)
{
	if (GetHud())
		GetHud()->Title = TEXT("");

	MouseClickSector.RemoveAll(this);
}
*/

void AFFGameSequence_GameTurns::OnActorClicked(AFFActor* Actor)
{


	// Deck or Discard Clicked
	// -> Sequence Choose in List

	// Own Ship Sector
	// -> 
	
}

void AFFGameSequence_GameTurns::OnActorEnter(AFFActor* Actor)
{
}

void AFFGameSequence_GameTurns::OnActorExit(AFFActor* Actor)
{
}


void AFFGameSequence_GameTurns::ServerReceiveResponse(int32 res)
{
	UE_LOG(Firefly, Log, TEXT("Receive response %d"), res);

	/*
	GetOwner<AFFGameSequence_Game>()->PlayerGameTurns(PlayersOrder[CurrentPlayerIndex], res);

	FinishPlayerGameTurns(PlayersOrder[CurrentPlayerIndex]);
		
	CurrentPlayerIndex--;

	if (CurrentPlayerIndex >= 0)
		StartPlayerGameTurns(PlayersOrder[CurrentPlayerIndex]);
	else
		ServerStopCurrentSequence();
	*/
}


