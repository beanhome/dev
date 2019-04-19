// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "GameSequence/SWSequence_Game.h"
#include "./SWSequence_OnePlayerTurn/SWSequence_MovePhase.h"
#include "./SWSequence_OnePlayerTurn/SWSequence_ShootPhase.h"
#include "./SWSequence_OnePlayerTurn/SWSequence_HandToHandPhase.h"
#include "GSSequence_Pause.h"
#include "UI/Page/SWGameHud.h"
#include "SWSequence_OnePlayerTurn.h"

void ASWSequence_OnePlayerTurn::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void ASWSequence_OnePlayerTurn::Start()
{
	Super::Start();

	if (IsClient())
	{
		ASWSequence_Game* SequenceOwner = GetOwner<ASWSequence_Game>();
		USWGameHud* Hud = (SequenceOwner ? SequenceOwner->GetGameHud() : nullptr);

		if (IsMyTurn())
		{
			if (Hud)
				Hud->Title = TEXT("It is your turn !");
		}
		else
		{
			if (Hud)
				Hud->Title = TEXT("Other Player Turn");
		}
	}
	else if (IsServer())
	{
		AddSubSequence<AGSSequence_Pause>(AGSSequence_Pause::FInit(1.f));
		AddSubSequence<ASWSequence_MovePhase>();
		AddSubSequence<ASWSequence_ShootPhase>();
		AddSubSequence<ASWSequence_HandToHandPhase>();
		//AddSubSequence<AGSSequence_Pause>(AGSSequence_Pause::FInit(1.f), this, &ASWSequence_OnePlayerTurn::OnEndTurnSequences);
		StartAllSubSequence();
	}
}

void ASWSequence_OnePlayerTurn::End()
{
	Super::End();

	ASWSequence_Game* SequenceOwner = GetOwner<ASWSequence_Game>();
	USWGameHud* Hud = (SequenceOwner ? SequenceOwner->GetGameHud() : nullptr);

	if (Hud)
		Hud->Title = TEXT("");
}

/*
bool ASWSequence_OnePlayerTurn::OnEndTurnSequences(AGSSequence* Seq)
{
	check(IsServer());

	FinishPlayerTurn(CurrentPlayerId);
	CurrentPlayerId = (CurrentPlayerId + 1) % GetGame()->GetPlayerCount();
	if (CurrentPlayerId == 0)
		CurrentTurn++;

	return true;
}
*/
