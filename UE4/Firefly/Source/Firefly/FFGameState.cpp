// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameState.h"

#include "Net/UnrealNetwork.h"
#include "Game/GameSequence/FFGameSequence_Game.h"

void AFFGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetOwner(GetWorld()->GetFirstPlayerController());
}

void AFFGameState::AddPlayerState(class APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
}

void AFFGameState::RemovePlayerState(class APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
}

void AFFGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AFFGameState, Game);
}

void AFFGameState::StartGame()
{
	if (Role == ROLE_Authority)
	{
		Game = GetWorld()->SpawnActor<AFFGameSequence_Game>();
		Game->ServerInit(nullptr);
		Game->ServerStart();
	}

	SetOwner(GetWorld()->GetFirstPlayerController());
}
