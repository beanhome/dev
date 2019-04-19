// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWPlayerController.h"


void ASWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (InputComponent)
	{
		InputComponent->BindAxis("MoveUp", this, &ASWPlayerController::MoveUpInput);
		InputComponent->BindAxis("MoveRight", this, &ASWPlayerController::MoveRightInput);
	}

	SetViewTarget(GetWorld()->SpawnActor<ACameraActor>());

	AActor* ViewTarget = GetViewTarget();
	ViewTarget->SetActorLocation(FVector(0.f, 0.f, 320.f));
	ViewTarget->SetActorRotation(FRotator(-50.f, -90.f, 0.f));

	/*
	static FName NAME_FreeCam = FName(TEXT("FreeCam"));
	if (PlayerCameraManager != nullptr)
		PlayerCameraManager->CameraStyle = NAME_FreeCam;
	*/
}

bool ASWPlayerController::HasCursorGroundLocation() const
{
	return CursorGroundHit.bBlockingHit;
}

FVector ASWPlayerController::GetCursorGroundLocation() const
{
	return CursorGroundHit.Location;
}

bool ASWPlayerController::HasCursorNavLocation() const
{
	return bHasCursorNav;
}

FVector ASWPlayerController::GetCursorNavLocation() const
{
	return CursorNavLocation;
}

void ASWPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	float Speed = 300.f;

	float Up = InputComponent->GetAxisValue("MoveUp");
	float Right = InputComponent->GetAxisValue("MoveRight");

	FVector Delta(Right * DeltaTime * Speed, -Up * DeltaTime * Speed, 0.f);

	AActor* ViewTarget = GetViewTarget();
	FVector CurrentLocation = ViewTarget->GetActorLocation();
	ViewTarget->SetActorLocation(CurrentLocation + Delta);
}


void ASWPlayerController::MoveUpInput(float Val)
{
}

void ASWPlayerController::MoveRightInput(float Val)
{
}

void ASWPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Project Mouse to get ground (exclude actor)
	FVector MouseLocation, MouseDirection;
	if (DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
	{
		FVector Start = MouseLocation;
		FVector End = MouseLocation + MouseDirection * 5000.f;
		
		FCollisionQueryParams QueryParams;
		GetWorld()->LineTraceSingleByChannel(CursorGroundHit, Start, End, ECC_Visibility, QueryParams);
	}

	CursorNavLocation = CursorGroundHit.Location;
	bHasCursorNav = false;

	// Find closest Nav Point of CursorGround
	if (CursorGroundHit.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), CursorGroundHit.Location, 5.f, 4, FColor::Blue);

		UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
		if (NavSys != nullptr)
		{
			FNavLocation Location;
			bHasCursorNav = NavSys->ProjectPointToNavigation(CursorGroundHit.Location, Location);

			if (bHasCursorNav)
			{
				FVector Start = Location.Location + FVector::UpVector * 16.f;
				FVector End = Location.Location + FVector::UpVector * -32.f;
				FHitResult Hit;
				FCollisionQueryParams QueryParams;
				bHasCursorNav = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);
				CursorNavLocation = (bHasCursorNav ? Hit.Location : Location.Location);
			}
		}
	}

	DrawDebugSphere(GetWorld(), CursorNavLocation, 5.f, 4, (bHasCursorNav ? FColor::Green : FColor::Red));
}