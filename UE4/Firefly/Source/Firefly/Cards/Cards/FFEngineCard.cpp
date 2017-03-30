// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFEngineCard.h"

AFFEngineCard::AFFEngineCard()
: MoveCount(5)
, FuelCost(1)
{
}

void AFFEngineCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AFFEngineCard::BeginPlay()
{
	Super::BeginPlay();
}

int32 AFFEngineCard::GetMoveCount() const
{
	return MoveCount;
}

int32 AFFEngineCard::GetFuelCost() const
{
	return FuelCost;
}
