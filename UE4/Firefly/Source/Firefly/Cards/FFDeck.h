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

	TSubclassOf<class AFFCard> DrawCard();
	void Discard(TSubclassOf<class AFFCard> CardClass);

	void Shuffle();

	const TArray<TSubclassOf<class AFFCard>>& GetCardList() const;
	TArray<TSubclassOf<class AFFActor>> GetCardListAsActor() const;
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
	TArray<TSubclassOf<class AFFCard>> CardListModel;

	UPROPERTY(ReplicatedUsing = OnRep_CardListChange)
	TArray<TSubclassOf<class AFFCard>> CardList;

	UPROPERTY(EditAnywhere)
	class AFFDiscardPile* DiscardPile;

	UPROPERTY(EditAnywhere)
	bool bShuffle;
};



