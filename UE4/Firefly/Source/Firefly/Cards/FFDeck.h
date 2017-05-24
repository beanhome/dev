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

private:
	void CreateMaterialInstance();
	void Init();

public:
	UPROPERTY(EditAnywhere)
	UTexture* BackTexture;

private:
	static FName BackTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* BackMaterial;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFFGameSequence_Card>> CardListModel;

	UPROPERTY()
	TArray<TSubclassOf<class AFFGameSequence_Card>> CardList;
};



