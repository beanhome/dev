// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "GameSequence/SWSequence_Game.h"
#include "SWSequence_OneGameTurn.h"
#include "SWSequence_OnePlayerTurn.h"
#include "GSPlayerController.h"


void ASWSequence_OneGameTurn::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);

	OnePlayerTurnSequence = ASWSequence_OnePlayerTurn::StaticClass();
}

void ASWSequence_OneGameTurn::Start()
{
	Super::Start();
}

void ASWSequence_OneGameTurn::End()
{
	Super::End();
}

FSWPlayer& ASWSequence_OneGameTurn::GetPlayingPlayer()
{
	ASWSequence_Game* Game = GetOwner<ASWSequence_Game>();
	check(Game);

	return Game->GetPlayer(CurrentPlayerId);
}

const FSWPlayer& ASWSequence_OneGameTurn::GetMyPlayer() const
{
	check(GetGSPlayerController());
	
	ASWSequence_Game* Game = GetOwner<ASWSequence_Game>();
	check(Game);

	return Game->GetPlayer(GetGSPlayerController()->GetId());
}

/*
void ASWSequence_OneGameTurn::BeginPlayerTurn()
{
	if (IsServer())
	{
		StartSubSequence<ASWSequence_OnePlayerTurn>(ASWSequence_OnePlayerTurn::FInit(PlayerCount), this, &ASWSequence_PlayerTurns::OnPlayerTurnFinish);
	}
}

void ASWSequence_OneGameTurn::OnPlayerTurnFinish(AGSSequence* Seq)
{
	Super::OnPlayerTurnFinish(Seq);
}

void ASWSequence_OneGameTurn::EndPlayerTurn()
{

}
*/

