// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence.h"
#include "GSSequence_OnePlayerTurn_Base.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEQUENCE_API AGSSequence_OnePlayerTurn_Base : public AGSSequence
{
	GENERATED_BODY()

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	bool IsTurnOf(int32 id) const;
	bool IsMyTurn() const;
};
