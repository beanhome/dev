// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_LoadStuff.h"
#include "FFTypes.h"
#include "Board/FFShipBoard.h"

AFFGameSequence_LoadStuff::AFFGameSequence_LoadStuff()
{
}

void AFFGameSequence_LoadStuff::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_LoadStuff::Start()
{
	Super::Start();

	if (IsServer())
	{
		FFFPlayer& Player = GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();

		for (int32 i = 0; i < Count; ++i)
			Player.ShipBoard->AddStuff(Stuff);

		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_LoadStuff::End()
{
	Super::End();
}

bool AFFGameSequence_LoadStuff::IsValidFor(const FFFPlayer& Player) const
{
	return !bNeedRoom || true /*Player.ShipBoard && Player.ShipBoard->HasEnoughRoom(Stuff, Count)*/;
}




