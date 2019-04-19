// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSequence/SWSequence_Game/SWSequence_OnePlayerTurn/SWSequence_SubTurn.h"
#include "SWSequence_HandToHandPhase.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_HandToHandPhase : public ASWSequence_SubTurn
{
	GENERATED_BODY()

	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

protected:

};
