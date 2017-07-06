// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFTypes.h"
#include "Cards/FFCard.h"
#include "FFNavCard.generated.h"

/** A card that can be clicked */
UCLASS(minimalapi)
class AFFNavCard : public AFFCard
{
	GENERATED_BODY()

public:
	AFFNavCard();

	friend class AFFGameSequence_Card;
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	TSubclassOf<class AFFGameSequence_Card> GetSequenceTemplate();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFFGameSequence_Card> SequenceTemplate;

	UPROPERTY(EditDefaultsOnly)
	TArray<struct FFFGSCardChoice> Choices;
};



