// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubTurn.h"

#include "FFGameSequence_DrawMultiCards.generated.h"

UCLASS(minimalapi)
class AFFGameSequence_DrawMultiCards : public AFFGameSequence_SubTurn
{
	GENERATED_BODY()

public:
	AFFGameSequence_DrawMultiCards();
	
	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	void SetDeck(class AFFDeck* Deck);
	void SetChoosenCount(int32 iCount);
	void SetPickCount(int32 iCount);

private:
	UFUNCTION()
	void OnChooseInDiscardValidate();
	UFUNCTION()
	void OnChooseInDiscardCancel();

	UFUNCTION()
	void OnChooseInSelectListValidate();
	UFUNCTION()
	void OnChooseInSelectListCancel();

	UFUNCTION()
	void OnFinishShuffleDeck(AFFGameSequence* Seq);

	void DrawAndPickCard();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFGameSequence_MultiChooseInList> ChooseInDiscardTemplate;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFGameSequence_MultiChooseInList> ChooseInSelectListTemplate;

	UPROPERTY(EditAnywhere)
	int32 ChoosenCount;

	UPROPERTY(EditAnywhere)
	int32 PickCount;

	UPROPERTY(Replicated)
	class AFFDeck* Deck;

	UPROPERTY()
	class AFFGameSequence_MultiChooseInList* DiscardList;

	UPROPERTY()
	class AFFGameSequence_MultiChooseInList* SelectList;

	TArray<TSubclassOf<AFFActor> > SelectListClass;
};



