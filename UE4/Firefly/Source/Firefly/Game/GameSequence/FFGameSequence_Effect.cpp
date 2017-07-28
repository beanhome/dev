// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Effect.h"

AFFGameSequence_Effect::AFFGameSequence_Effect()
{
}

void AFFGameSequence_Effect::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_Effect::Start()
{
	Super::Start();
}

void AFFGameSequence_Effect::End()
{
	Super::End();
}

bool AFFGameSequence_Effect::IsValidFor(const struct FFFPlayer& Player) const
{
	return true;
}


