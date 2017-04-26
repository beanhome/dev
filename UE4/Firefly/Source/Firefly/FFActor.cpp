// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFActor.h"
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

	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
		GameState->Game->PropagateMouseEnterActor(this);
}

void AFFActor::OnMouseExit()
{
	MouseOver = false;
	ActorMouseExitDelegate.Broadcast(this);

	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
		GameState->Game->PropagateMouseExitActor(this);
}

void AFFActor::OnMouseClick()
{
	ActorMouseClickDelegate.Broadcast(this);

	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
		GameState->Game->PropagateMouseClickActor(this);

	//GetFFPlayerController()->JumpToCamera(Camera);
}


