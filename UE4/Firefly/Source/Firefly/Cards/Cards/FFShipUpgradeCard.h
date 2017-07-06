// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Cards/Cards/FFSupplyCard.h"
#include "FFShipUpgradeCard.generated.h"

/** A card that can be clicked */
UCLASS(minimalapi)
class AFFShipUpgradeCard : public AFFSupplyCard
{
	GENERATED_BODY()

public:
	AFFShipUpgradeCard();
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
};



