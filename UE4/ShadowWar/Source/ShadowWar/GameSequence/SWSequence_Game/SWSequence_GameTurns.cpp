// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "GameSequence/SWSequence_Game.h"
#include "SWSequence_OneGameTurn.h"
#include "SWSequence_GameTurns.h"


void ASWSequence_GameTurns::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void ASWSequence_GameTurns::Start()
{
	Super::Start();
}

void ASWSequence_GameTurns::End()
{
	Super::End();
}

void ASWSequence_GameTurns::BeginGameTurn()
{
	if (IsServer())
	{
		int32 PlayerCount = GetOwner<ASWSequence_Game>()->GetPlayerCount();

		StartSubSequence<ASWSequence_OneGameTurn>(ASWSequence_OneGameTurn::FInit(PlayerCount), this, &ASWSequence_GameTurns::OnGameTurnFinish);
	}
}

void ASWSequence_GameTurns::OnGameTurnFinish(AGSSequence* Seq)
{
	Super::OnGameTurnFinish(Seq);
}

void ASWSequence_GameTurns::EndGameTurn()
{

}

