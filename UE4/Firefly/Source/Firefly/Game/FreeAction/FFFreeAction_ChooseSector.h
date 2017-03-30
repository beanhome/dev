// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFFreeAction.h"
#include "Game/FFPathFinder.h"
#include "FFFreeAction_ChooseSector.generated.h"

class UFFPathFinder;

UCLASS(minimalapi)
class UFFFreeAction_ChooseSector : public UFFFreeAction
{
	GENERATED_BODY()

public:
	UFFFreeAction_ChooseSector();

	virtual void Start() override;
	virtual void Stop() override;
	virtual void Pause() override;
	virtual void Resume() override;

	UFUNCTION()
	void OnMouseEnterSector(AFFSector* Sector);

	UFUNCTION()
	void OnMouseExitSector(AFFSector* Sector);

	UFUNCTION()
	void OnMouseClickSector(AFFSector* Sector);

private:
};



