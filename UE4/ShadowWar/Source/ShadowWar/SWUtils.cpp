// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ShadowWar.h"
#include "SWUtils.h"
#include "Game/SWGameTuning.h"
#include "Game/SWUITuning.h"

const USWGameTuning* GetDefaultGameTuning()
{
	static ConstructorHelpers::FObjectFinder<UClass> GameTuningFinder(TEXT("Class'/Game/Tuning/GameTuning.GameTuning_C'"));
	check(GameTuningFinder.Object);
	return CastChecked<USWGameTuning>(GameTuningFinder.Object->GetDefaultObject());
}

const USWUITuning* GetDefaultUITuning()
{
	static ConstructorHelpers::FObjectFinder<UClass> UITuningFinder(TEXT("Class'/Game/Tuning/UITuning.UITuning_C'"));
	check(UITuningFinder.Object);
	return CastChecked<USWUITuning>(UITuningFinder.Object->GetDefaultObject());
}