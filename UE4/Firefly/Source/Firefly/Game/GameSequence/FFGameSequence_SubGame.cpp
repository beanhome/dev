// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_SubGame.h"
#include "FFGameSequence_Game.h"

AFFGameSequence_SubGame::AFFGameSequence_SubGame()
{
}

void AFFGameSequence_SubGame::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_SubGame::Start()
{
	Super::Start();
}

void AFFGameSequence_SubGame::End()
{
	Super::End();
}

UFFGameHud* AFFGameSequence_SubGame::GetHud()
{
	AFFGameSequence_Game* SequenceOwner = GetOwner<AFFGameSequence_Game>();
	return (SequenceOwner ? SequenceOwner->GetGameHud() : nullptr);
}
