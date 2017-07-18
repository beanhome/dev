// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubGame.h"

#include "FFGameSequence_PrimeDiscard.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_PrimeDiscard : public AFFGameSequence_SubGame
{
	GENERATED_BODY()

public:
	AFFGameSequence_PrimeDiscard();

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	void SetDeck(class AFFDeck* _Deck);

private:
	void OnEndTimer();

private:
	UPROPERTY(Replicated)
	class AFFDeck* Deck;
};



