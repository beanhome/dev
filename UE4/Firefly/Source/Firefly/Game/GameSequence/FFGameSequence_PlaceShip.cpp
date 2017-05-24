// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_PlaceShip.h"
#include "FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"
#include "FFGameSequence_SubGame.h"
#include "FFGameSequence_ChooseInList.h"
#include "Board/FFSector.h"

AFFGameSequence_PlaceShip::AFFGameSequence_PlaceShip()
{
}

void AFFGameSequence_PlaceShip::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

bool AFFGameSequence_PlaceShip::IsCameraFree() const
{
	return true;
}

void AFFGameSequence_PlaceShip::ServerStart()
{
	Super::ServerStart();

	PlayersOrder = GetOwner<AFFGameSequence_Game>()->GetPlayersOrder();

	CurrentPlayerIndex = PlayersOrder.Num() - 1;

	StartPlayerPlaceShip(PlayersOrder[CurrentPlayerIndex]);
}


void AFFGameSequence_PlaceShip::Start()
{
	Super::Start();
}

void AFFGameSequence_PlaceShip::End()
{
	Super::End();

	if (Hover)
		Hover->HighLight(false);
}

void AFFGameSequence_PlaceShip::StartPlayerPlaceShip_Implementation(int32 id)
{
	CurrentPlayerId = id;

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (PlayerController)
	{
		if (PlayerController->GetId() == id)
		{
			if (GetHud())
				GetHud()->Title = TEXT("Place Your Ship");

			UE_LOG(FFSeq, Log, TEXT("*******  AFFGameSequence_PlaceShip::StartPlayer %d MY TURN"), GetMyPlayerId());
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("An other player place his ship");

			UE_LOG(FFSeq, Log, TEXT("*******  AFFGameSequence_PlaceShip::StartPlayer %d OTHER TURN"), GetMyPlayerId());
		}
	}
}

void AFFGameSequence_PlaceShip::FinishPlayerPlaceShip_Implementation(int32 id)
{
	if (GetHud())
		GetHud()->Title = TEXT("");

	if (Hover)
		Hover->HighLight(false);
}

bool AFFGameSequence_PlaceShip::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	if (IsServer())
		return false;

	if (PlayerId != CurrentPlayerId)
		return false;

	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	if (GetMyPlayerId() == CurrentPlayerId)
	{
		if (IsUnderCamera(CameraName) == false)
			return false;

		Sector->HighLight(false);

		// useless with function called in server too
		SendResponseToServer(Sector->GetId());

		return true;
	}

	return false;
}

bool AFFGameSequence_PlaceShip::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	if (IsServer())
		return false;

	if (PlayerId != CurrentPlayerId)
		return false;

	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	Sector->HighLight(true);

	Hover = Sector;

	return true;
}

bool AFFGameSequence_PlaceShip::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	if (IsServer())
		return false;

	if (PlayerId != CurrentPlayerId)
		return false;

	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	if (Hover == Sector)
		Sector->HighLight(false);

	Hover = nullptr;

	return true;
}

void AFFGameSequence_PlaceShip::ServerReceiveResponse(int32 res)
{
	GetGame()->PlayerPlaceShip(CurrentPlayerId, res);

	FinishPlayerPlaceShip(CurrentPlayerId);
		
	CurrentPlayerIndex--;

	if (CurrentPlayerIndex >= 0)
		StartPlayerPlaceShip(PlayersOrder[CurrentPlayerIndex]);
	else
		ServerStopCurrentSequence();
}


