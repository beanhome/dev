// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWSequence_SubTurn.h"
#include "GameSequence/SWSequence_Game.h"
#include "GameSequence/SWSequence_Game/SWSequence_GameTurns.h"
#include "GameSequence/SWSequence_Game/SWSequence_OneGameTurn.h"
#include "GameSequence/SWSequence_Game/SWSequence_OnePlayerTurn.h"

const FSWPlayer& ASWSequence_SubTurn::GetPlayer(int32 id) const
{
	return GetOwner<ASWSequence_Game>()->GetPlayer(id);
}

const FSWPlayer& ASWSequence_SubTurn::GetMyPlayer() const
{
	return GetOwner<ASWSequence_OneGameTurn>()->GetMyPlayer();
}

FSWPlayer& ASWSequence_SubTurn::GetPlayingPlayer() const
{
	return GetOwner<ASWSequence_OneGameTurn>()->GetPlayingPlayer();
}

bool ASWSequence_SubTurn::IsTurnOf(int32 id) const
{
	if (State == EGSClientState::Ended)
		return false;

	return GetOwner<AGSSequence_OnePlayerTurn_Base>()->IsTurnOf(id);
}

bool ASWSequence_SubTurn::IsMyTurn() const
{
	if (State == EGSClientState::Ended)
		return false;

	return GetOwner<AGSSequence_OnePlayerTurn_Base>()->IsMyTurn();
}
