// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameState.h"
//#include "GSSequence_Main.h"
#include "GSGameState.generated.h"

UCLASS()
class GAMESEQUENCE_API AGSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void AddPlayerState(class APlayerState* PlayerState);
	virtual void RemovePlayerState(class APlayerState* PlayerState);

	void StartGame(const TSubclassOf<class AGSSequence_Main>& MainGameSequenceClass);

	bool IsActorInteractive() const;

public:
	UPROPERTY(replicated)
	class AGSSequence_Main* Main;
};



