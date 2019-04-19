// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWSequence_MovePhase.h"
#include "./SWSequence_MovePhase/SWSequence_PrepareMove.h"
#include "UI/Page/SWGameHud.h"

void ASWSequence_MovePhase::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void ASWSequence_MovePhase::Start()
{
	Super::Start();

	if (IsClient())
	{
		if (IsMyTurn())
		{
			if (GetHud())
				GetHud()->Title = TEXT("Movement Phase !");
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("Other Player Turn");
		}
	}
	else if (IsServer())
	{
		AddSubSequence<ASWSequence_PrepareMove>();
		StopAutoAfterAllSubSequence();
		StartAllSubSequence();
	}
}

void ASWSequence_MovePhase::End()
{
	Super::End();
}