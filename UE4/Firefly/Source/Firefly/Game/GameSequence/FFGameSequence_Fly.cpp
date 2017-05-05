// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Fly.h"
#include "FFGameSequence_GameTurns.h"
#include "Game/FireflyPlayerController.h"
#include "Board/FFSector.h"
#include "Game/FFPathFinder.h"

AFFGameSequence_Fly::AFFGameSequence_Fly()
	: PathFinder(nullptr)
{
}

void AFFGameSequence_Fly::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

bool AFFGameSequence_Fly::IsCameraFree() const
{
	return true;
}

void AFFGameSequence_Fly::ServerStart()
{
	Super::ServerStart();

}

void AFFGameSequence_Fly::Start()
{
	Super::Start();

	if (IsClient() && GetOwner<AFFGameSequence_GameTurns>()->IsMyTurn())
	{
		const FFFPlayer& Player = GetOwner<AFFGameSequence_GameTurns>()->GetGame()->GetPlayer(GetMyPlayerId());
		AFFSector* ShipSector = Player.Ship->GetCurrentSector();

		PathFinder = NewObject<UFFPathFinder>(this);
		FFFPath Zone;
		PathFinder->GetSectorsAtDist(ShipSector, 5, Zone);

		for (const FFFPathNode& Node : Zone.Path)
		{
			DrawDebugString(GetWorld(), Node.Sector->GetCenter() - FVector(0.f, 50.f, 0.f), FString::Printf(TEXT("%d"), Node.PathCost), nullptr, FColor::White, -1.f);
		}
	}
}

void AFFGameSequence_Fly::End()
{
	Super::End();
}

bool AFFGameSequence_Fly::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	return true;
}

bool AFFGameSequence_Fly::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	Sector->SetActorHiddenInGame(false);

	return true;
}

bool AFFGameSequence_Fly::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	Sector->SetActorHiddenInGame(true);

	return true;
}
