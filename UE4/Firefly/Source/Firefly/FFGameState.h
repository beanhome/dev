// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
#include "FFGameState.generated.h"

UCLASS(ClassGroup = "Firefly")
class AFFGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void AddPlayerState(class APlayerState* PlayerState);
	virtual void RemovePlayerState(class APlayerState* PlayerState);

	void StartGame();

	bool IsCameraFree() const;
	bool IsActorInteractive() const;

public:
	UPROPERTY(replicated)
	class AFFGameSequence_Game* Game;

	//UPROPERTY()
	//AFFGameSequence* CurrentSequence;
};



