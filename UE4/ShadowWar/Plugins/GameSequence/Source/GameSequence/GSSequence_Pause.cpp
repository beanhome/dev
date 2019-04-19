// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GameSequence.h"
#include "GSSequence_Pause.h"
#include "GSPlayerController.h"

void AGSSequence_Pause::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);

	if (InitParameter != nullptr)
		Delay = ((AGSSequence_Pause::FInit*)InitParameter)->Delay;
}

void AGSSequence_Pause::Start()
{
	Super::Start();

	if (IsServer())
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGSSequence_Pause::OnEndTimer, Delay);
}

void AGSSequence_Pause::End()
{
	Super::End();

	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AGSSequence_Pause::OnEndTimer()
{
	check(IsServer());

	ServerStopCurrentSequence();
}