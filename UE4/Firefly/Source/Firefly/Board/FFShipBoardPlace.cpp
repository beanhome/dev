// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFShipBoardPlace.h"

AFFShipBoardPlace::AFFShipBoardPlace()
{
}

void AFFShipBoardPlace::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UStaticMeshComponent*> Components;
	
	GetComponents(Components);

	for (UStaticMeshComponent* Component : Components)
	{
		if (Component->GetName() == "CrewMesh")
			Crew = Component;
		else if (Component->GetName() == "EngineMesh")
			Engine = Component;
	}
}

FVector AFFShipBoardPlace::GetCrewLocation() const
{
	return (Crew != nullptr ? Crew->GetComponentLocation() : GetActorLocation());
}

FVector AFFShipBoardPlace::GetEngineLocation() const
{
	return (Engine != nullptr ? Engine->GetComponentLocation() : GetActorLocation());
}

