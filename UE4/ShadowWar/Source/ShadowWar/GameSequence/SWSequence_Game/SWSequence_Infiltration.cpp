// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWSequence_Infiltration.h"

void ASWSequence_Infiltration::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void ASWSequence_Infiltration::Start()
{
	Super::Start();

	if (IsServer())
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASWSequence_Infiltration::InterruptInfiltration, 1.f);
	}
}

void ASWSequence_Infiltration::End()
{
	Super::End();
}

void ASWSequence_Infiltration::InterruptInfiltration()
{
	check(IsServer());

	ServerStopCurrentSequence();
}

