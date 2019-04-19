// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSequence/SWSequence_SubGame.h"
#include "SWSequence_Infiltration.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_Infiltration : public ASWSequence_SubGame
{
	GENERATED_BODY()

	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

protected:
	void InterruptInfiltration();

};
