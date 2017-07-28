// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFCrewCard.h"

AFFCrewCard::AFFCrewCard()
{
}


void AFFCrewCard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFCrewCard, bDisgruntled);
}

void AFFCrewCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AFFCrewCard::BeginPlay()
{
	Super::BeginPlay();
}

bool AFFCrewCard::IsDisgruntled() const
{
	return bDisgruntled;
}

void AFFCrewCard::SetDisgruntled(bool bSet)
{
	bDisgruntled = bSet;
}

