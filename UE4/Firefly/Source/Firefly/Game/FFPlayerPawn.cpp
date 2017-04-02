// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFPlayerPawn.h"
#include "Board/FFSector.h"
#include "DrawDebugHelpers.h"

AFFPlayerPawn::AFFPlayerPawn()
{
	GetStaticMeshComponent()->OnClicked.AddDynamic(this, &AFFPlayerPawn::SectorClicked);
	GetStaticMeshComponent()->OnBeginCursorOver.AddDynamic(this, &AFFPlayerPawn::SectorBeginCursorOver);
	GetStaticMeshComponent()->OnEndCursorOver.AddDynamic(this, &AFFPlayerPawn::SectorEndCursorOver);
}

void AFFPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentSector)
	{
		FVector Loc = CurrentSector->GetCenter();
		FVector Extent = CurrentSector->GetExtent();

		FVector PawnCenter;
		FVector PawnExtent;
		GetActorBounds(true, PawnCenter, PawnExtent);

		SetActorLocation(Loc + FVector::UpVector * (Extent.Z + PawnExtent.Z));

		/*
		UFFPathFinder* PathFinder = NewObject<UFFPathFinder>(this);
		FFFPath Zone;
		PathFinder->GetSectorsAtDist(CurrentSector, 5, Zone);

		for (const FFFPathNode& Node : Zone.Path)
		{
			DrawDebugString(GetWorld(), Node.Sector->GetCenter() - FVector(0.f, 50.f, 0.f), FString::Printf(TEXT("%d"), Node.PathCost), nullptr, FColor::White, -1.f);
		}
		*/
	}
}


void AFFPlayerPawn::SectorClicked(UPrimitiveComponent* ClickedComp, FKey Key)
{
	//UE_LOG(Firefly, Log, TEXT("%s Clicked"), *GetName());
}

void AFFPlayerPawn::SectorBeginCursorOver(UPrimitiveComponent* ClickedComp)
{
	//UE_LOG(Firefly, Log, TEXT("%s BeginCursorOver"), *GetName());
}

void AFFPlayerPawn::SectorEndCursorOver(UPrimitiveComponent* ClickedComp)
{
	//UE_LOG(Firefly, Log, TEXT("%s EndCursorOver"), *GetName());
}
