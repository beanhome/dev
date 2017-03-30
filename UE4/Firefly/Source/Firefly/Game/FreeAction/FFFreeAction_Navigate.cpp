// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFFreeAction_Navigate.h"

#include "Game/FFGameTurn.h"
#include "Game/FFPlayerInfo.h"
#include "Game/FFPathFinder.h"
#include "Board/FFSector.h"
#include "Cards/Cards/FFEngineCard.h"

UFFFreeAction_Navigate::UFFFreeAction_Navigate()
{
	PathFinder = NewObject<UFFPathFinder>(this, TEXT("FFFreeAction_Navigate_PathFinder"));
}

void UFFFreeAction_Navigate::Start()
{
	/*
	UFFPlayerInfo* Player = GameTurn->GetCurrentPlayer();
	check(Player);

	AFFSector* CurrentSector = Player->GetCurrentSector();
	int32 MoveCount = (Player->GetEngine() != nullptr ? Player->GetEngine()->GetMoveCount() : 5);

	PathFinder->GetSectorsAtDist(CurrentSector, MoveCount, Zone);

	for (const FFFPathNode& Node : Zone.Path)
		Node.Sector->SetActorHiddenInGame(false);
	*/
}

void UFFFreeAction_Navigate::Stop()
{
	for (const FFFPathNode& Node : Zone.Path)
		Node.Sector->SetActorHiddenInGame(true);
}

void UFFFreeAction_Navigate::Pause()
{
	for (const FFFPathNode& Node : Zone.Path)
		Node.Sector->SetActorHiddenInGame(true);
}

void UFFFreeAction_Navigate::Resume()
{
	for (const FFFPathNode& Node : Zone.Path)
		Node.Sector->SetActorHiddenInGame(false);
}


