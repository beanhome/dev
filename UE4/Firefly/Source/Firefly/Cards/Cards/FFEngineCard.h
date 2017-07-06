// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Cards/Cards/FFShipUpgradeCard.h"
#include "FFEngineCard.generated.h"

/** A card that can be clicked */
UCLASS(minimalapi)
class AFFEngineCard : public AFFShipUpgradeCard
{
	GENERATED_BODY()

public:
	AFFEngineCard();
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	int32 GetMoveCount() const;
	int32 GetFuelCost() const;

private:
	UPROPERTY(EditAnywhere)
	int32 MoveCount;

	UPROPERTY(EditAnywhere)
	int32 FuelCost;
};



