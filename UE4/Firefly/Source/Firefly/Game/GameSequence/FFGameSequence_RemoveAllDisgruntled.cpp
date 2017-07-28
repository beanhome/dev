// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_RemoveAllDisgruntled.h"
#include "FFTypes.h"
#include "Board/FFShipBoard.h"

AFFGameSequence_RemoveAllDisgruntled::AFFGameSequence_RemoveAllDisgruntled()
{
}

void AFFGameSequence_RemoveAllDisgruntled::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_RemoveAllDisgruntled::Start()
{
	Super::Start();

	if (IsServer())
	{
		FFFPlayer& Player = GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();

		Player.ShipBoard->RemoveAllDisgruntled();

		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_RemoveAllDisgruntled::End()
{
	Super::End();
}



