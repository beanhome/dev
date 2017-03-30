// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_PlaceShip.h"
#include "FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"
#include "FFGameSequence_SubGame.h"
#include "FFGameSequence_ChooseInList.h"

AFFGameSequence_PlaceShip::AFFGameSequence_PlaceShip()
{
}

void AFFGameSequence_PlaceShip::Init(AFFGameSequence* OwnerSequence)
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_PlaceShip::Init %s"), *GetFFPlayerController()->GetName());

	Super::Init(OwnerSequence);
}

void AFFGameSequence_PlaceShip::ServerStart()
{
	Super::ServerStart();

	PlayersOrder = GetOwner<AFFGameSequence_Game>()->GetPlayersOrder();

	CurrentPlayerIndex = PlayersOrder.Num()-1;

	StartPlayerPlaceShip(PlayersOrder[CurrentPlayerIndex]);
}


void AFFGameSequence_PlaceShip::Start()
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_PlaceShip::Start %s"), *GetFFPlayerController()->GetName());

	Super::Start();
}

void AFFGameSequence_PlaceShip::End()
{
	if (GetFFPlayerController())
		UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_PlaceShip::End %s"), *GetFFPlayerController()->GetName());

	Super::End();
}

void AFFGameSequence_PlaceShip::StartPlayerPlaceShip_Implementation(int32 id)
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (PlayerController)
	{
		if (PlayerController->GetId() == id)
		{
			if (GetHud())
				GetHud()->Title = TEXT("Place Your Ship");

			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_PlaceShip::StartPlayer %s MY TURN"), *GetFFPlayerController()->GetName());

			MouseClickSector.AddDynamic(this, &AFFGameSequence_PlaceShip::OnSectorClicked);
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("An other player place his ship");

			UE_LOG(Firefly, Log, TEXT("*******  AFFGameSequence_PlaceShip::StartPlayer %s OTHER TURN"), *GetFFPlayerController()->GetName());
		}
	}
}

void AFFGameSequence_PlaceShip::FinishPlayerPlaceShip_Implementation(int32 id)
{
	if (GetHud())
		GetHud()->Title = TEXT("");

	MouseClickSector.RemoveAll(this);
}

void AFFGameSequence_PlaceShip::OnSectorClicked(AFFSector* SectorClicked)
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (PlayerController != nullptr && CameraName.IsEmpty() == false && PlayerController->GetCurrentCamera() != nullptr)
	{
		if (PlayerController->GetCurrentCamera()->GetName() != CameraName)
			return;
	}

	GetFFPlayerController()->SendResponseToServer(SectorClicked->GetId());
}

void AFFGameSequence_PlaceShip::ServerReceiveResponse(int32 res)
{
	UE_LOG(Firefly, Log, TEXT("Receive response %d"), res);

	// Set ship loc to info
	// ...

	FinishPlayerPlaceShip(PlayersOrder[CurrentPlayerIndex]);
		
	CurrentPlayerIndex--;

	if (CurrentPlayerIndex >= 0)
		StartPlayerPlaceShip(PlayersOrder[CurrentPlayerIndex]);
	else
		ServerStopCurrentSequence();
}


