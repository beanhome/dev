// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFCard.generated.h"

/** A card that can be clicked */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFCard : public AFFActor
{
	GENERATED_BODY()

public:
	AFFCard();
	virtual ~AFFCard();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

	void CreateMaterialInstance();

public:
	UPROPERTY(EditAnywhere)
	UTexture* FrontTexture;

	UPROPERTY(EditAnywhere)
	UTexture* BackTexture;

private:
	static FName FrontTextureName;
	static FName BackTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* FrontMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* BackMaterial;
};



