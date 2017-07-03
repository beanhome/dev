// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_KeepFlying.h"

AFFGameSequence_KeepFlying::AFFGameSequence_KeepFlying()
{
}

void AFFGameSequence_KeepFlying::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_KeepFlying::Start()
{
	Super::Start();

	if (IsServer())
		ServerStopCurrentSequence();
}

void AFFGameSequence_KeepFlying::End()
{
	Super::End();
}


