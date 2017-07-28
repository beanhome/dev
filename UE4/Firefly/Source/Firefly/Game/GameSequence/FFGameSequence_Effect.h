// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_Effect.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_Effect : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_Effect();

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual bool IsValidFor(const struct FFFPlayer& Player) const;
	
private:

};



