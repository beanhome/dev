// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFFreeAction.h"
#include "Game/FFPathFinder.h"
#include "FFFreeAction_Navigate.generated.h"

class UFFPathFinder;

UCLASS(minimalapi)
class UFFFreeAction_Navigate : public UFFFreeAction
{
	GENERATED_BODY()

public:
	UFFFreeAction_Navigate();

	virtual void Start() override;
	virtual void Stop() override;
	virtual void Pause() override;
	virtual void Resume() override;

private:
	UPROPERTY()
	UFFPathFinder* PathFinder;

	UPROPERTY()
	FFFPath Zone;
};



