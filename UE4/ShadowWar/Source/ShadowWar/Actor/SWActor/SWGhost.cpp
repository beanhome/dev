// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWGhost.h"
#include "UnrealNetwork.h"

ASWGhost::ASWGhost()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ASWGhost::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ASWGhost::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASWGhost, Fighter);
}

const ASWFighter* ASWGhost::GetFighter() const
{
	return Fighter;
}

ASWFighter*ASWGhost::GetFighter()
{
	return Fighter;
}

void ASWGhost::SetFighter(ASWFighter* NewFighter)
{
	Fighter = NewFighter;
}


