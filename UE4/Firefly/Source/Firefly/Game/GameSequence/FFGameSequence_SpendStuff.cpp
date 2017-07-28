// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_SpendStuff.h"
#include "FFTypes.h"
#include "Board/FFShipBoard.h"

AFFGameSequence_SpendStuff::AFFGameSequence_SpendStuff()
{
}

void AFFGameSequence_SpendStuff::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_SpendStuff::Start()
{
	Super::Start();

	if (IsServer())
	{
		FFFPlayer& Player = GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();

		for (int32 i = 0; i < Count; ++i)
			Player.ShipBoard->RemStuff(Stuff);

		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_SpendStuff::End()
{
	Super::End();
}

bool AFFGameSequence_SpendStuff::IsValidFor(const FFFPlayer& Player) const
{
	return Player.ShipBoard && Player.ShipBoard->HasStuff(Stuff, Count);
}




