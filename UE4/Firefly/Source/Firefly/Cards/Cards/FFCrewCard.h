// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Cards/Cards/FFSupplyCard.h"
#include "FFCrewCard.generated.h"

/** A card that can be clicked */
UCLASS(minimalapi)
class AFFCrewCard : public AFFSupplyCard
{
	GENERATED_BODY()

public:
	AFFCrewCard();
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
};



