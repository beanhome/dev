// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_ChooseLeaderAndShip.h"
#include "FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"
#include "FFGameSequence_SubGame.h"
#include "FFGameSequence_ChooseInList.h"

AFFGameSequence_ChooseLeaderAndShip::AFFGameSequence_ChooseLeaderAndShip()
{
}

void AFFGameSequence_ChooseLeaderAndShip::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_ChooseLeaderAndShip::ServerStart()
{
	Super::ServerStart();

	const AFFGameSequence_ChooseInList* ChooseLeaderDefault = GetDefaultGameTuning()->GameSequence_ChooseLeader.GetDefaultObject();
	const AFFGameSequence_ChooseInList* ChooseShipDefault = GetDefaultGameTuning()->GameSequence_ChooseShip.GetDefaultObject();

	if (ChooseLeaderDefault)
	{
		for (const TSubclassOf<AFFActor>& Card : ChooseLeaderDefault->GetList())
			LeaderCards.Add(Card);
	}

	if (ChooseShipDefault)
	{
		for (const TSubclassOf<AFFActor>& Card : ChooseShipDefault->GetList())
			Ships.Add(Card);
	}

	PlayersOrder = GetOwner<AFFGameSequence_Game>()->GetPlayersOrder();

	CurrentPlayerIndex = 0;
	ChoosePhase = EFFPhase::Leader;

	StartPlayerChooseLeader(PlayersOrder[CurrentPlayerIndex], LeaderCards);
}


void AFFGameSequence_ChooseLeaderAndShip::Start()
{
	Super::Start();
}

void AFFGameSequence_ChooseLeaderAndShip::End()
{
	Super::End();
}

void AFFGameSequence_ChooseLeaderAndShip::StartPlayerChooseLeader_Implementation(int32 id, const TArray<TSubclassOf<AFFActor>>& NewLeaderCards)
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	LeaderCards = NewLeaderCards;

	if (PlayerController)
	{
		if (PlayerController->GetId() == id)
		{
			if (GetHud())
				GetHud()->Title = TEXT("Choose your leader");

			Log(TEXT("MY TURN"));

			ChooseInList = StartLocalSubSequence<AFFGameSequence_ChooseInList>(GetDefaultGameTuning()->GameSequence_ChooseLeader, AFFGameSequence_ChooseInList::FInit(LeaderCards));
			ChooseInList->ChooseInListDelegate.AddDynamic(this, &AFFGameSequence_ChooseLeaderAndShip::OnLeaderCardChoosen);
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("An other player choose his leader");

			Log(TEXT("OTHER TURN"));
		}
	}
}

void AFFGameSequence_ChooseLeaderAndShip::FinishPlayerChooseLeader_Implementation(int32 id)
{
	if (GetHud())
		GetHud()->Title = TEXT("");
}

void AFFGameSequence_ChooseLeaderAndShip::StartPlayerChooseShip_Implementation(int32 id, const TArray<TSubclassOf<AFFActor>>& NewShips)
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	Ships = NewShips;

	if (PlayerController)
	{
		if (PlayerController->GetId() == id)
		{
			if (GetHud())
				GetHud()->Title = TEXT("Choose your ship");

			Log(TEXT("MY TURN"));

			ChooseInList = StartLocalSubSequence<AFFGameSequence_ChooseInList>(GetDefaultGameTuning()->GameSequence_ChooseShip, AFFGameSequence_ChooseInList::FInit(Ships));
			ChooseInList->ChooseInListDelegate.AddDynamic(this, &AFFGameSequence_ChooseLeaderAndShip::OnShipChoosen);
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("An other player choose his ship");

			Log(TEXT("OTHER TURN"));
		}
	}
}

void AFFGameSequence_ChooseLeaderAndShip::FinishPlayerChooseShip_Implementation(int32 id)
{
	if (GetHud())
		GetHud()->Title = TEXT("");
}


void AFFGameSequence_ChooseLeaderAndShip::OnLeaderCardChoosen(int32 id)
{
	StopLocalSubSequence(ChooseInList);
	ChooseInList = nullptr;

	SendResponseToServer(id);
}

void AFFGameSequence_ChooseLeaderAndShip::OnShipChoosen(int32 id)
{
	StopLocalSubSequence(ChooseInList);
	ChooseInList = nullptr;

	SendResponseToServer(id);
}

void AFFGameSequence_ChooseLeaderAndShip::ServerReceiveResponse(int32 res)
{
	UE_LOG(FFSeq, Log, TEXT("Receive response %d"), res);

	switch (ChoosePhase)
	{
		case EFFPhase::Leader:
			GetOwner<AFFGameSequence_Game>()->PlayerChooseLeader(PlayersOrder[CurrentPlayerIndex], LeaderCards[res]);
			LeaderCards.RemoveAt(res);
			FinishPlayerChooseLeader(PlayersOrder[CurrentPlayerIndex]);
			ChoosePhase = EFFPhase::Ship;
			StartPlayerChooseShip(PlayersOrder[CurrentPlayerIndex], Ships);
			break;

		case EFFPhase::Ship:
			GetOwner<AFFGameSequence_Game>()->PlayerChooseShip(PlayersOrder[CurrentPlayerIndex], Ships[res]);
			Ships.RemoveAt(res);
			FinishPlayerChooseShip(PlayersOrder[CurrentPlayerIndex]);
			CurrentPlayerIndex++;
			ChoosePhase = EFFPhase::Leader;
			if (CurrentPlayerIndex < PlayersOrder.Num())
				StartPlayerChooseLeader(PlayersOrder[CurrentPlayerIndex], LeaderCards);
			else
				ServerStopCurrentSequence();
			break;
	}
}


