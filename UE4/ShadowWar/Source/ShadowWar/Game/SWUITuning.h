// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once


#include "SWUITuning.generated.h"


UCLASS(Blueprintable, ClassGroup = "ShadowWar")
class USWUITuning : public UObject
{
	GENERATED_BODY()

public:
	USWUITuning();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LobbyPageClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WaitingPageClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USWGameHud> GameHUDClass;
};



