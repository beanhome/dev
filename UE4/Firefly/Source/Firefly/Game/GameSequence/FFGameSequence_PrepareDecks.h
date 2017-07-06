// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubGame.h"

#include "FFGameSequence_PrepareDecks.generated.h"

class AFFCameraActor;

UCLASS(minimalapi)
class AFFGameSequence_PrepareDecks : public AFFGameSequence_SubGame
{
	GENERATED_BODY()

public:
	AFFGameSequence_PrepareDecks();
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual bool IsCameraFree() const;



private:
	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	bool ShuffleDeckStart();
	UFUNCTION()
	void ShuffleDeckFinish(AFFGameSequence* Seq);
	
	bool PrimeDiscardStart();
	UFUNCTION()
	void PrimeDiscardFinish(AFFGameSequence* Seq);

private:
	TArray<class AFFDeck*> Decks;
	int32 Index;
};



