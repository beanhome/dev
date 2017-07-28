// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_Effect.h"

#include "FFGameSequence_SpendStuff.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_SpendStuff : public AFFGameSequence_Effect
{
	GENERATED_BODY()

public:
	AFFGameSequence_SpendStuff();

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual bool IsValidFor(const struct FFFPlayer& Player) const override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFStuff> Stuff;

	UPROPERTY(EditAnywhere)
	int32 Count;
};



