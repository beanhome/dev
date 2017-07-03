// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFDeck.generated.h"

/** A block that can be clicked */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFDeck : public AFFActor
{
	GENERATED_BODY()

public:
	AFFDeck();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

	TSubclassOf<class AFFGameSequence_Card> DrawCard();
	void Discard(TSubclassOf<class AFFGameSequence_Card> CardClass);

	void Shuffle();

	const TArray<TSubclassOf<class AFFGameSequence_Card>>& GetCardList() const;
	class AFFDiscardPile* GetDiscardPile();

private:
	void CreateMaterialInstance();
	void Init();

	UFUNCTION()
	void OnRep_CardListChange();

public:
	UPROPERTY(EditAnywhere)
	UTexture* BackTexture;

private:
	static FName BackTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* BackMaterial;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFFGameSequence_Card>> CardListModel;

	UPROPERTY(ReplicatedUsing = OnRep_CardListChange)
	TArray<TSubclassOf<class AFFGameSequence_Card>> CardList;

	UPROPERTY(EditAnywhere)
	class AFFDiscardPile* DiscardPile;

};



