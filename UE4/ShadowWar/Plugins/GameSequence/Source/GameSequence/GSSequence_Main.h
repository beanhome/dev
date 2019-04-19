// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GSSequence.h"
#include "GSSequence_Main.generated.h"

UCLASS()
class GAMESEQUENCE_API AGSSequence_Main : public AGSSequence
{
	GENERATED_BODY()

public:
	AGSSequence_Main();

public:
	UFUNCTION(Reliable, NetMulticast)
	void ReceiveMouseEnterActor(int32 PlayerId, class AGSActor* Actor);

	UFUNCTION(Reliable, NetMulticast)
	void ReceiveMouseLeaveActor(int32 PlayerId, class AGSActor* Actor);

	UFUNCTION(Reliable, NetMulticast)
	void ReceiveMouseClickActor(int32 PlayerId, class AGSActor* Actor);
};



