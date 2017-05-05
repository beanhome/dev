// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFActor.h"
#include "Game/GameSequence/FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"

AFFActor::AFFActor()
{
	MouseOver = false;
}

AFireflyPlayerController* AFFActor::GetFFPlayerController() const
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	return (GameInstance != nullptr ? Cast<AFireflyPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);
}

FVector AFFActor::GetCenter() const
{
	return Center;
}

FVector AFFActor::GetExtent() const
{
	return Extent;
}

void AFFActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (GetRootComponent() != nullptr)
	{
		FBox Box = GetRootComponent()->Bounds.GetBox();
		Box.GetCenterAndExtents(Center, Extent);
	}
}

void AFFActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetRootComponent() != nullptr)
	{
		FBox Box = GetRootComponent()->Bounds.GetBox();
		Box.GetCenterAndExtents(Center, Extent);
	}
}

void AFFActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFFActor::SetLocation(const FVector& loc)
{
	SetActorLocation(loc);
	GetActorBounds(true, Center, Extent);
}

void AFFActor::SetRotation(const FRotator& rot)
{
	SetActorRotation(rot);
	GetActorBounds(true, Center, Extent);
}


void AFFActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFFActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AFFActor::OnMouseEnter()
{
	MouseOver = true;
	ActorMouseEnterDelegate.Broadcast(this);

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (Role == ROLE_Authority)
	{
		// Local
		AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
		if (GameState != nullptr && GameState->Game != nullptr)
			GameState->Game->PropagateMouseEnterActor(PlayerController->GetId(), this);
	}
	else
	{
		// Replicated
		PlayerController->SendClientMouseEnterActor(this);
	}
}

void AFFActor::OnMouseLeave()
{
	MouseOver = false;
	ActorMouseLeaveDelegate.Broadcast(this);

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (Role == ROLE_Authority)
	{
		// Local
		AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
		if (GameState != nullptr && GameState->Game != nullptr)
			GameState->Game->PropagateMouseLeaveActor(PlayerController->GetId(), this);
	}
	else
	{
		// Replicated
		PlayerController->SendClientMouseLeaveActor(this);
	}
}

void AFFActor::OnMouseClick()
{
	ActorMouseClickDelegate.Broadcast(this);

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (Role == ROLE_Authority)
	{
		// Local
		AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
		if (GameState != nullptr && GameState->Game != nullptr)
			GameState->Game->PropagateMouseClickActor(PlayerController->GetId(), this);
	}
	else
	{
		// Replicated
		PlayerController->SendClientMouseClickActor(this);
	}
}


