// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Cards/FFCard.h"
#include "FFSupplyCard.generated.h"

/** A card that can be clicked */
UCLASS(minimalapi)
class AFFSupplyCard : public AFFCard
{
	GENERATED_BODY()

public:
	AFFSupplyCard();
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

private:
};



