// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubTurn.h"

#include "FFGameSequence_VisitDiscard.generated.h"

UCLASS(minimalapi)
class AFFGameSequence_VisitDiscard : public AFFGameSequence_SubTurn
{
	GENERATED_BODY()

public:
	AFFGameSequence_VisitDiscard();
	
	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	void SetDiscard(class AFFDiscardPile* _Discard);

	virtual void OnValidate() override;
	virtual void OnCancel() override;

private:
	UPROPERTY(Replicated)
	class AFFDiscardPile* Discard;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFFGameSequence_ChooseInList> ChooseListTemplate;
	
	UPROPERTY()
	class AFFGameSequence_ChooseInList* ChoiceList;
};



