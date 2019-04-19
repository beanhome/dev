// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GameSequence.h"
#include "GSGameState.h"
#include "GSSequence_Main.h"

#include "Net/UnrealNetwork.h"

void AGSGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetOwner(GetWorld()->GetFirstPlayerController());
}

void AGSGameState::AddPlayerState(class APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
}

void AGSGameState::RemovePlayerState(class APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
}

void AGSGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AGSGameState, Main);
}

void AGSGameState::StartGame(const TSubclassOf<AGSSequence_Main>& MainGameSequenceClass)
{
	if (Role == ROLE_Authority)
		Main = GetWorld()->SpawnActor<AGSSequence_Main>(MainGameSequenceClass);

	SetOwner(GetWorld()->GetFirstPlayerController());
}

bool AGSGameState::IsActorInteractive() const
{
	return (Main != nullptr && Main->IsActorInteractive());
}



