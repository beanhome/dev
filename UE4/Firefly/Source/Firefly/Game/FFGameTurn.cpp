// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameTurn.h"
#include "Game/FreeAction/FFFreeAction_Navigate.h"
#include "Game/FreeAction/FFFreeAction_ChooseSector.h"

AFFGameTurn::AFFGameTurn()
{
}

void AFFGameTurn::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}


void AFFGameTurn::Start()
{
	/*
	UFFFreeAction_Navigate* FreeActionNav = NewObject<UFFFreeAction_Navigate>(this);
	FreeActionNav->Init(this);
	FreeActionNav->Start();

	FreeActions.Add(FreeActionNav);
	*/

	UFFFreeAction_ChooseSector* FreeActionChoose = NewObject<UFFFreeAction_ChooseSector>(this);
	FreeActionChoose->Init(this);
	FreeActionChoose->Start();

	FreeActions.Add(FreeActionChoose);
}

void AFFGameTurn::End()
{
	for (UFFFreeAction* FreeAction : FreeActions)
	{
		FreeAction->Stop();
	}
}

