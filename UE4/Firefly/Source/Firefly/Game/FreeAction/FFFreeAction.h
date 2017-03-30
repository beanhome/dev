// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFFreeAction.generated.h"

class UFFPlayerInfo;
class AFFGameTurn;

UCLASS(minimalapi)
class UFFFreeAction : public UObject
{
	GENERATED_BODY()

public:
	UFFFreeAction();

	virtual void Init(AFFGameTurn* GT);

	virtual void Start();
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();

protected:
	UPROPERTY()
	AFFGameTurn* GameTurn;
};



