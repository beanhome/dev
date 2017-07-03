// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFDiscardPile.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class AFFDiscardPile : public AFFActor
{
	GENERATED_BODY()

public:
	AFFDiscardPile();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

	void AddCard(TSubclassOf<class AFFGameSequence_Card> CardClass);

	const TArray<TSubclassOf<class AFFGameSequence_Card>>& GetCardList() const;

	void Empty();

private:
	void CreateMaterialInstance();

	UFUNCTION()
	void OnRep_CardListChange();

public:
	UPROPERTY(EditAnywhere)
	UTexture* DiscardTexture;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFGameSequence_MultiChooseInList> MultiChooseInListTemplate;

private:
	static FName FrontTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* DiscardMaterial;

	UPROPERTY(ReplicatedUsing = OnRep_CardListChange)
	TArray<TSubclassOf<class AFFGameSequence_Card>> CardList;
};



