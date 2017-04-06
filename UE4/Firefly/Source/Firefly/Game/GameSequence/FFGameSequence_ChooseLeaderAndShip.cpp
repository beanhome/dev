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
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseLeaderAndShip::Init %s"), *GetFFPlayerController()->GetName());

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
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseLeaderAndShip::Start %s"), *GetFFPlayerController()->GetName());

	Super::Start();
}

void AFFGameSequence_ChooseLeaderAndShip::End()
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseLeaderAndShip::End %s"), *GetFFPlayerController()->GetName());

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

			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseLeaderAndShip::StartPlayer %s MY TURN"), *GetFFPlayerController()->GetName());

			ChooseInList = StartLocalSubSequence<AFFGameSequence_ChooseInList>(GetDefaultGameTuning()->GameSequence_ChooseLeader, AFFGameSequence_ChooseInList::FInit(LeaderCards));
			ChooseInList->ChooseInListDelegate.AddDynamic(this, &AFFGameSequence_ChooseLeaderAndShip::OnLeaderCardChoosen);
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("An other player choose his leader");

			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseLeaderAndShip::StartPlayer %s OTHER TURN"), *GetFFPlayerController()->GetName());
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

			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseShip::StartPlayer %s MY TURN"), *GetFFPlayerController()->GetName());

			ChooseInList = StartLocalSubSequence<AFFGameSequence_ChooseInList>(GetDefaultGameTuning()->GameSequence_ChooseShip, AFFGameSequence_ChooseInList::FInit(Ships));
			ChooseInList->ChooseInListDelegate.AddDynamic(this, &AFFGameSequence_ChooseLeaderAndShip::OnShipChoosen);
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("An other player choose his ship");

			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_ChooseShip::StartPlayer %s OTHER TURN"), *GetFFPlayerController()->GetName());
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
	ChooseInList->End();
	ChooseInList->Destroy();
	ChooseInList = nullptr;
	SubSequence = nullptr;

	SendResponseToServer(id);
}

void AFFGameSequence_ChooseLeaderAndShip::OnShipChoosen(int32 id)
{
	ChooseInList->End();
	ChooseInList->Destroy();
	ChooseInList = nullptr;
	SubSequence = nullptr;

	SendResponseToServer(id);
}

void AFFGameSequence_ChooseLeaderAndShip::ServerReceiveResponse(int32 res)
{
	UE_LOG(Firefly, Log, TEXT("Receive response %d"), res);

	switch (ChoosePhase)
	{
		case EFFPhase::Leader:
			// Set Leader to info
			// ...
			LeaderCards.RemoveAt(res);
			FinishPlayerChooseLeader(PlayersOrder[CurrentPlayerIndex]);
			ChoosePhase = EFFPhase::Ship;
			StartPlayerChooseShip(PlayersOrder[CurrentPlayerIndex], Ships);
			break;

		case EFFPhase::Ship:
			// Set ship to info
			// ...
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


