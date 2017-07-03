// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_Effect.h"

#include "FFGameSequence_FullStop.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_FullStop : public AFFGameSequence_Effect
{
	GENERATED_BODY()

public:
	AFFGameSequence_FullStop();

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;
	
private:

};



