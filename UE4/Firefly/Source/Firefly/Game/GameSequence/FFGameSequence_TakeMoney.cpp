// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_TakeMoney.h"
#include "FFTypes.h"
#include "Board/FFShipBoard.h"

AFFGameSequence_TakeMoney::AFFGameSequence_TakeMoney()
{
}

void AFFGameSequence_TakeMoney::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_TakeMoney::Start()
{
	Super::Start();

	if (IsServer())
	{
		FFFPlayer& Player = GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();

		Player.Credits += Amount;
		Player.ShipBoard->RefreshCredits(Player.Credits);

		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_TakeMoney::End()
{
	Super::End();
}



