// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "UI/Page/FFGameHud.h"
#include "UI/Page/FFQuestionPopup.h"

#include "FFUITuning.generated.h"


UCLASS(Blueprintable, ClassGroup = "Firefly")
class UFFUITuning : public UObject
{
	GENERATED_BODY()

public:
	UFFUITuning();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LobbyPageClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WaitingPageClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFFGameHud> GameHUDClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFFQuestionPopup> QuestionPopupClass;
		
};



