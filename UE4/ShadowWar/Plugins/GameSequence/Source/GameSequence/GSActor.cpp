// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GameSequence.h"
#include "GSActor.h"
#include "GSGameState.h"
#include "GSSequence_Main.h"
#include "GSPlayerController.h"
#include "Engine/World.h"

AGSActor::AGSActor()
{
	MouseOver = false;
}

AGSPlayerController* AGSActor::GetGSPlayerController() const
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	return (GameInstance != nullptr ? Cast<AGSPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);
}

bool AGSActor::IsServer() const
{
	return GetWorld()->GetAuthGameMode() != nullptr;
}

bool AGSActor::IsClient() const
{
	return GetWorld()->GetAuthGameMode() == nullptr;
}

void AGSActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AGSActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGSActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGSActor::SetLocation(const FVector& loc)
{
	SetActorLocation(loc);
}

void AGSActor::SetRotation(const FRotator& rot)
{
	SetActorRotation(rot);
}

void AGSActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGSActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AGSActor::OnMouseEnter()
{
	MouseOver = true;
	ActorMouseEnterDelegate.Broadcast(this);

	AGSPlayerController* PlayerController = GetGSPlayerController();

	if (Role == ROLE_Authority)
	{
		// Local
		AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
		if (GameState != nullptr && GameState->Main != nullptr)
			GameState->Main->PropagateMouseEnterActor(PlayerController->GetId(), this);
	}
	else
	{
		// Replicated
		PlayerController->SendClientMouseEnterActor(this);
	}
}

void AGSActor::OnMouseLeave()
{
	MouseOver = false;
	ActorMouseLeaveDelegate.Broadcast(this);

	AGSPlayerController* PlayerController = GetGSPlayerController();

	if (Role == ROLE_Authority)
	{
		// Local
		AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
		if (GameState != nullptr && GameState->Main != nullptr)
			GameState->Main->PropagateMouseLeaveActor(PlayerController->GetId(), this);
	}
	else
	{
		// Replicated
		PlayerController->SendClientMouseLeaveActor(this);
	}
}

void AGSActor::OnMouseClick()
{
	ActorMouseClickDelegate.Broadcast(this);

	AGSPlayerController* PlayerController = GetGSPlayerController();

	if (Role == ROLE_Authority)
	{
		// Local
		AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
		if (GameState != nullptr && GameState->Main != nullptr)
			GameState->Main->PropagateMouseClickActor(PlayerController->GetId(), this);
	}
	else
	{
		// Replicated
		PlayerController->SendClientMouseClickActor(this);
	}
}


