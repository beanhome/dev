// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_AllCrewDisgruntled.h"
#include "FFTypes.h"
#include "Board/FFShipBoard.h"

AFFGameSequence_AllCrewDisgruntled::AFFGameSequence_AllCrewDisgruntled()
{
}

void AFFGameSequence_AllCrewDisgruntled::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_AllCrewDisgruntled::Start()
{
	Super::Start();

	if (IsServer())
	{
		FFFPlayer& Player = GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();

		Player.ShipBoard->MakeAllCrewDisgruntled();

		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_AllCrewDisgruntled::End()
{
	Super::End();
}



