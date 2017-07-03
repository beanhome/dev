// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFStuff.generated.h"

/** A card that can be clicked */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFStuff : public AFFActor
{
	GENERATED_BODY()

public:
	AFFStuff();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

	void CreateMaterialInstance();

	bool IsIllegal() const;
	bool IsSmall() const;

public:
	UPROPERTY(EditAnywhere)
	UTexture* FrontTexture;

protected:
	UPROPERTY(EditAnywhere)
	bool Illegal;

	UPROPERTY(EditAnywhere)
	bool Small;

private:
	static FName FrontTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* FrontMaterial;
};



