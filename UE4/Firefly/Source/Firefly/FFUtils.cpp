// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFUtils.h"
#include "Game/FFGameTuning.h"
#include "Game/FFUITuning.h"

const UFFGameTuning* GetDefaultGameTuning()
{
	static ConstructorHelpers::FObjectFinder<UClass> GameTuningFinder(TEXT("Class'/Game/Firefly/Tuning/GameTuning.GameTuning_C'"));
	check(GameTuningFinder.Object);
	return CastChecked<UFFGameTuning>(GameTuningFinder.Object->GetDefaultObject());
}

const UFFUITuning* GetDefaultUITuning()
{
	static ConstructorHelpers::FObjectFinder<UClass> UITuningFinder(TEXT("Class'/Game/Firefly/Tuning/UITuning.UITuning_C'"));
	check(UITuningFinder.Object);
	return CastChecked<UFFUITuning>(UITuningFinder.Object->GetDefaultObject());
}