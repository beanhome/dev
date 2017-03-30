// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameSequence/FFGameSequence.h"

#include "FFGameTurn.generated.h"

class UFFFreeAction;

UCLASS(minimalapi)
class AFFGameTurn : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameTurn();
	
	virtual void Init(AFFGameSequence* OwnerSequence) override;

	virtual void Start() override;
	virtual void End() override;

private:
	UPROPERTY()
	TArray<UFFFreeAction*> FreeActions;

public:
};



