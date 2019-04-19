// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence_GameTurns_Base.h"
#include "SWSequence_GameTurns.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_GameTurns : public AGSSequence_GameTurns_Base
{
	GENERATED_BODY()

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void BeginGameTurn();
	virtual void EndGameTurn();

protected:
	UFUNCTION()
	void OnGameTurnFinish(AGSSequence* Seq);

	//FSWPlayer& GetPlayingPlayer();
	//const FSWPlayer& GetMyPlayer() const;
};
