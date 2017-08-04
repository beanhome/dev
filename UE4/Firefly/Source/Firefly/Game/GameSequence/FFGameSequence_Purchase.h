// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_Effect.h"

#include "FFGameSequence_Purchase.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_Purchase : public AFFGameSequence_Effect
{
	GENERATED_BODY()

public:
	AFFGameSequence_Purchase();

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void OnValidate() override;
	virtual void OnCancel() override;
	
private:
	UPROPERTY(EditAnywhere)
	TArray<FFFPurchaseStuff> Stuffs;

};



