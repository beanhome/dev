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

private:
	void CreateMaterialInstance();

public:
	UPROPERTY(EditAnywhere)
	UTexture* DiscardTexture;

private:
	static FName FrontTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* DiscardMaterial;
};



