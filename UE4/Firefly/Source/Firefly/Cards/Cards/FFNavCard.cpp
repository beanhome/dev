// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFNavCard.h"

AFFNavCard::AFFNavCard()
{
}

void AFFNavCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AFFNavCard::BeginPlay()
{
	Super::BeginPlay();
}

TSubclassOf<class AFFGameSequence_Card> AFFNavCard::GetSequenceTemplate()
{
	return SequenceTemplate;
}

