// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFShipBoardPlace.generated.h"

/** The Ship Board of each player */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFShipBoardPlace : public AFFActor
{
	GENERATED_BODY()

public:
	AFFShipBoardPlace();

	friend class AFFShipBoard;

	virtual void PostInitializeComponents() override;

	FVector GetCrewLocation(int32 id = 0) const;
	FVector GetEngineLocation() const;

private:
	UPROPERTY()
	TArray<UStaticMeshComponent*> Crew;

	UPROPERTY()
	UStaticMeshComponent* Engine;

	UPROPERTY()
	TArray<UStaticMeshComponent*> Upgrade;
};
