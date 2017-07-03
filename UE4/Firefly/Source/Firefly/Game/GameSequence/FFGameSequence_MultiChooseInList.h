// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubTurn.h"

#include "FFGameSequence_MultiChooseInList.generated.h"

UCLASS(minimalapi)
class AFFGameSequence_MultiChooseInList : public AFFGameSequence_SubTurn
{
	GENERATED_BODY()

public:
	AFFGameSequence_MultiChooseInList();
	
	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	void SetClassList(const TArray<TSubclassOf<class AFFActor>>& List);
	void SetCardList(const TArray<TSubclassOf<class AFFGameSequence_Card>>& List);
	void SetMax(int32 iMax);

	UFUNCTION()
	void OnChoiceListSelect(int32 id);
	
	UFUNCTION()
	void OnChoosenListSelect(int32 id);

	virtual void OnValidate() override;
	virtual void OnCancel() override;

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFFActor>> ClassList;

	UPROPERTY(Replicated, EditAnywhere)
	TArray<TSubclassOf<class AFFGameSequence_Card>> CardList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFFGameSequence_ChooseInList> ChooseListTemplate;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFFGameSequence_ChooseInList> ChoosenListTemplate;

	UPROPERTY(EditAnywhere)
	int32 Maximum;

	UPROPERTY()
	class AFFGameSequence_ChooseInList* ChoiceList;

	UPROPERTY()
	class AFFGameSequence_ChooseInList* ChoosenList;
};



