// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_FullStop.h"
#include "FFGameSequence_Fly.h"

AFFGameSequence_FullStop::AFFGameSequence_FullStop()
{
}

void AFFGameSequence_FullStop::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_FullStop::Start()
{
	Super::Start();

	if (IsServer())
	{
		GetOwner<AFFGameSequence_Fly>()->FullStop();
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_FullStop::End()
{
	Super::End();
}


