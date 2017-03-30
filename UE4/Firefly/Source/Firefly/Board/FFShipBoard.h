// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFShipBoard.generated.h"

/** The Ship Board of each player */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFShipBoard : public AFFActor
{
	GENERATED_BODY()

public:
	AFFShipBoard();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void CreateMaterialInstance();

public:
	UPROPERTY(EditAnywhere)
	UTexture* FrontTexture;

private:
	static FName FrontTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* FrontMaterial;
};
