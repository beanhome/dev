// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence_OnePlayerTurn_Base.h"
#include "SWSequence_OnePlayerTurn.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_OnePlayerTurn : public AGSSequence_OnePlayerTurn_Base
{
	GENERATED_BODY()

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	//FSWPlayer& GetPlayingPlayer();
	//const FSWPlayer& GetMyPlayer() const;
};
