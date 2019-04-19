// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GSSequence.h"
#include "GSSequence_Pause.generated.h"

UCLASS()
class GAMESEQUENCE_API AGSSequence_Pause : public AGSSequence
{
	GENERATED_BODY()

public:
	struct FInit : public FGSSequenceInit
	{
		FInit(float _Delay) : Delay(_Delay) {}
		FInit(const FInit& orig) : Delay(orig.Delay) {}
		float Delay;
	};

	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

protected:
	void OnEndTimer();

protected:
	UPROPERTY(EditAnywhere)
	float Delay;

	UPROPERTY()
	FTimerHandle TimerHandle;
};



