// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_SubTurn.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_GameTurns.h"

AFFGameSequence_SubTurn::AFFGameSequence_SubTurn()
{
}

AFFGameSequence_Game* AFFGameSequence_SubTurn::GetGame() const
{
	return GetOwner<AFFGameSequence_Game>();
}

UFFGameHud* AFFGameSequence_SubTurn::GetHud() const
{
	return GetGame()->GetGameHud();
}

const FFFPlayer& AFFGameSequence_SubTurn::GetPlayer(int32 id) const
{
	return GetGame()->GetPlayer(id);
}

const FFFPlayer& AFFGameSequence_SubTurn::GetPlayingPlayer() const
{
	return GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();
}

bool AFFGameSequence_SubTurn::IsTurnOf(int32 id) const
{
	return GetOwner<AFFGameSequence_GameTurns>()->IsTurnOf(id);
}

bool AFFGameSequence_SubTurn::IsMyTurn() const
{
	return GetOwner<AFFGameSequence_GameTurns>()->IsMyTurn();
}
