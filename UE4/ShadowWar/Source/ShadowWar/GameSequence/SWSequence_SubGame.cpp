// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ShadowWar.h"
#include "SWSequence_SubGame.h"
#include "SWSequence_Game.h"

ASWSequence_SubGame::ASWSequence_SubGame()
{
}

void ASWSequence_SubGame::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void ASWSequence_SubGame::Start()
{
	Super::Start();
}

void ASWSequence_SubGame::End()
{
	Super::End();
}

const ASWSequence_Game* ASWSequence_SubGame::GetGame() const
{
	return GetOwner<ASWSequence_Game>();
}

ASWSequence_Game* ASWSequence_SubGame::GetGame()
{
	return GetOwner<ASWSequence_Game>();
}

USWGameHud* ASWSequence_SubGame::GetHud()
{
	ASWSequence_Game* SequenceOwner = GetOwner<ASWSequence_Game>();
	return (SequenceOwner ? SequenceOwner->GetGameHud() : nullptr);
}
