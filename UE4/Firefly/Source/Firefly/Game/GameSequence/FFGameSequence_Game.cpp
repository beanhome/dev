// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FireflyGameMode.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_ChooseLeaderAndShip.h"
#include "FFGameSequence_PlaceShip.h"
#include "Game/FireflyPlayerController.h"
#include "Game/FFUITuning.h"
#include "UI/Page/FFGameHud.h"

AFFGameSequence_Game::AFFGameSequence_Game()
{
}

UFFGameHud* AFFGameSequence_Game::GetGameHud()
{
	return GameHUD;
}

const TArray<int32>& AFFGameSequence_Game::GetPlayersOrder() const
{
	return PlayersOrder;
}

void AFFGameSequence_Game::Init(AFFGameSequence* OwnerSequence)
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_Game::Init %s"), *GetFFPlayerController()->GetName());

	Super::Init(OwnerSequence);
}


void AFFGameSequence_Game::Start()
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (PlayerController)
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_Game::Start %s"), *GetFFPlayerController()->GetName());

	Super::Start();

	const UFFUITuning* UITuning = GetDefaultUITuning();
	if (PlayerController && UITuning->GameHUDClass.GetDefaultObject())
	{
		GameHUD = CreateWidget<UFFGameHud>(PlayerController, UITuning->GameHUDClass);
		GameHUD->AddToViewport();

		GameHUD->Id = PlayerController->GetId();
		GameHUD->Title = GetClass()->GetName();
	}

	if (Role == ROLE_Authority)
	{
		ShufflePlayerOrder();

		StartSubSequence<AFFGameSequence_ChooseLeaderAndShip>();
		SubSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Game::ChooseLeaderAndShipFinish);
	}
}

void AFFGameSequence_Game::ChooseLeaderAndShipFinish(AFFGameSequence* Seq)
{
	UE_LOG(Firefly, Log, TEXT("*******  ChooseLeaderAndShipFinish"));

	SubSequence = nullptr;
	//StopSubSequence();

	StartSubSequence<AFFGameSequence_PlaceShip>(GetDefaultGameTuning()->GameSequence_PlaceShip);
	SubSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Game::PlaceShipFinish);
}

void AFFGameSequence_Game::PlaceShipFinish(AFFGameSequence* Seq)
{
	UE_LOG(Firefly, Log, TEXT("*******  PlaceShipFinish"));

	SubSequence = nullptr;
	//StopSubSequence();

}

void AFFGameSequence_Game::End()
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_Game::End %s"), *GetFFPlayerController()->GetName());

	if (GameHUD != nullptr)
	{
		GameHUD->RemoveFromParent();
		GameHUD = nullptr;
	}

	Super::End();
}

void AFFGameSequence_Game::ShufflePlayerOrder()
{
	AFireflyGameMode* const GameMode = GetWorld()->GetAuthGameMode<AFireflyGameMode>();
	check(GameMode != nullptr);

	int32 Size = GameMode->GetPlayers().Num();
	PlayersOrder.SetNum(Size);
	for (int32 i = 0; i < Size; ++i)
		PlayersOrder[i] = i;
	for (int32 i = 0; i < Size; ++i)
		PlayersOrder.Swap(i, FMath::RandRange(0, Size-1));
}
