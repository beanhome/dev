// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Engine/StaticMeshActor.h"
#include "FFPlayerPawn.generated.h"

/** A block that can be clicked */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFPlayerPawn : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AFFPlayerPawn();
	virtual void BeginPlay() override;

	UFUNCTION()
	void SectorClicked(UPrimitiveComponent* ClickedComp, FKey Key);

	UFUNCTION()
	void SectorBeginCursorOver(UPrimitiveComponent* ClickedComp);

	UFUNCTION()
	void SectorEndCursorOver(UPrimitiveComponent* ClickedComp);

public:
	UPROPERTY(EditAnywhere)
	class AFFSector* CurrentSector;
};



