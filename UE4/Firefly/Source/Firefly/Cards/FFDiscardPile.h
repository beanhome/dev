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

	void AddCard(TSubclassOf<class AFFCard> CardClass);
	void RemCard(TSubclassOf<class AFFCard> CardClass);

	const TArray<TSubclassOf<class AFFCard>>& GetCardList() const;
	TArray<TSubclassOf<class AFFActor>> GetCardListAsActor() const;

	void Empty();
	bool IsEmpty() const;

	class AFFDeck* GetDeck() const;
	void SetDeck(class AFFDeck*);

private:
	void CreateMaterialInstance();

	UFUNCTION()
	void OnRep_CardListChange();

public:
	UPROPERTY(EditAnywhere)
	UTexture* DiscardTexture;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFGameSequence_DrawMultiCards> DrawMultiCardTemplate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFGameSequence_VisitDiscard> VisitDiscardTemplate;

private:
	static FName FrontTextureName;

	class AFFDeck* Deck;

	UPROPERTY()
	UMaterialInstanceDynamic* DiscardMaterial;

	UPROPERTY(ReplicatedUsing = OnRep_CardListChange)
	TArray<TSubclassOf<class AFFCard>> CardList;
};



