// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GameSequence.h"
#include "GSSequence_Main.h"
#include "GSPlayerController.h"

AGSSequence_Main::AGSSequence_Main()
{
}

void AGSSequence_Main::ReceiveMouseEnterActor_Implementation(int32 PlayerId, class AGSActor* Actor)
{
	PropagateMouseEnterActor(PlayerId, Actor);
}

void AGSSequence_Main::ReceiveMouseLeaveActor_Implementation(int32 PlayerId, class AGSActor* Actor)
{
	PropagateMouseLeaveActor(PlayerId, Actor);
}

void AGSSequence_Main::ReceiveMouseClickActor_Implementation(int32 PlayerId, class AGSActor* Actor)
{
	PropagateMouseClickActor(PlayerId, Actor);
}
