// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_Shuffle.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_Shuffle : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_Shuffle();

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	void ShuffleDeck(class AFFDeck* _Deck);
	
private:
	UPROPERTY(Replicated)
	class AFFDeck* Deck;
};



