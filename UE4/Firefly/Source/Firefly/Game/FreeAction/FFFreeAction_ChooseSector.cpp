// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFFreeAction_ChooseSector.h"

#include "Game/FFGameTurn.h"
#include "Game/FFPlayerInfo.h"
#include "Board/FFSector.h"

UFFFreeAction_ChooseSector::UFFFreeAction_ChooseSector()
{
}

void UFFFreeAction_ChooseSector::Start()
{
	GameTurn->MouseEnterSector.AddDynamic(this, &UFFFreeAction_ChooseSector::OnMouseEnterSector);
	GameTurn->MouseExitSector.AddDynamic(this, &UFFFreeAction_ChooseSector::OnMouseExitSector);
	GameTurn->MouseClickSector.AddDynamic(this, &UFFFreeAction_ChooseSector::OnMouseClickSector);

}

void UFFFreeAction_ChooseSector::Stop()
{
	//for (const FFFPathNode& Node : Zone.Path)
	//	Node.Sector->SetActorHiddenInGame(true);
}

void UFFFreeAction_ChooseSector::Pause()
{
	//for (const FFFPathNode& Node : Zone.Path)
	//	Node.Sector->SetActorHiddenInGame(true);
}

void UFFFreeAction_ChooseSector::Resume()
{
	//for (const FFFPathNode& Node : Zone.Path)
	//	Node.Sector->SetActorHiddenInGame(false);
}

void UFFFreeAction_ChooseSector::OnMouseEnterSector(AFFSector* Sector)
{
	Sector->SetActorHiddenInGame(false);
}

void UFFFreeAction_ChooseSector::OnMouseExitSector(AFFSector* Sector)
{
	Sector->SetActorHiddenInGame(true);
}

void UFFFreeAction_ChooseSector::OnMouseClickSector(AFFSector* Sector)
{

}
