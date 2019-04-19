// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence_Main.h"
#include "SWTypes.h"
#include "SWSequence_Game.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_Game : public AGSSequence_Main
{
	GENERATED_BODY()

public:
	virtual void Start() override;
	virtual void End() override;

	class USWGameHud* GetGameHud();

	FSWPlayer& GetPlayer(int32 Id);
	const FSWPlayer& GetPlayer(int32 Id) const;
	int32 GetPlayerCount() const;

	UFUNCTION()
	bool OnInfiltrationFinish(AGSSequence* Seq);

protected:
	UPROPERTY()
	class USWGameHud* GameHUD;

	UPROPERTY()
	TArray<FSWPlayer> Players;
};
