// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "GSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEQUENCE_API AGSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGSGameModeBase();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void StartGame();

protected:
	UPROPERTY()
	int32 PlayerCount;

	UPROPERTY()
	class AGSPlayerController* HostPlayer;

	UPROPERTY()
	TSubclassOf<class AGSSequence_Main> MainGameSequenceClass;
};
