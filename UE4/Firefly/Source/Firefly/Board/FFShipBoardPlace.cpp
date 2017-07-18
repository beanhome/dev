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
		FString CompName = Component->GetName();

		if (CompName.StartsWith("CrewMesh"))
		{
			CompName.RemoveFromStart("CrewMesh");
			int32 Index = CompName[0] - '0';
			if (Index >= Crew.Num())
				Crew.SetNum(Index+1);
			Crew[Index] = Component;
		}
		else if (CompName.StartsWith("SlotMesh"))
		{
			CompName.RemoveFromStart("SlotMesh");
			int32 Index = CompName[0] - '0' -1;
			if (Index >= Upgrade.Num())
				Upgrade.SetNum(Index + 1);
			Upgrade[Index] = Component;
		}
		else if (Component->GetName() == "EngineMesh")
		{
			Engine = Component;
		}
	}
}

FVector AFFShipBoardPlace::GetCrewLocation(int32 id) const
{
	ensure(id >= 0 && id < Crew.Num());

	if (Crew.Num() == 0 || id < 0 || id >= Crew.Num())
		return GetActorLocation();

	return Crew[id]->GetComponentLocation();
}

FVector AFFShipBoardPlace::GetEngineLocation() const
{
	return (Engine != nullptr ? Engine->GetComponentLocation() : GetActorLocation());
}

