// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "SWGameTuning.generated.h"


UCLASS(Blueprintable, ClassGroup = "ShadowWar")
class USWGameTuning : public UObject
{
	GENERATED_BODY()

public:
	USWGameTuning();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGSSequence_Main> MainGameSequenceClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASWGhost> GhostTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASWFighter> FighterTemplate;
};



