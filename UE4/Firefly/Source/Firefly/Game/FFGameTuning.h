// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFGameTuning.generated.h"

class AFFEngineCard;
class AFFPlayerPawn;
class AFFShipBoard;
class AFFLeaderCard;


UCLASS(Blueprintable, ClassGroup = "Firefly")
class UFFGameTuning : public UObject
{
	GENERATED_BODY()

public:
	UFFGameTuning();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFFPlayerPawn> DefaultPlayerPawn;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFFShipBoard> DefaultShipBoard;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFFEngineCard> DefaultEngine;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFFGameSequence_ChooseInList> GameSequence_ChooseLeader;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFFGameSequence_ChooseInList> GameSequence_ChooseShip;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFFGameSequence_PlaceShip> GameSequence_PlaceShip;

	UPROPERTY(EditDefaultsOnly)
	float SwitchCameraDuration;
};



