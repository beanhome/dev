// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFCameraManager.h"
#include "FFCameraActor.h"
#include "Game/FireflyPlayerController.h"
#include "Game/FFGameTuning.h"

UFFCameraManager::UFFCameraManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	CameraConfig = nullptr;
	PlayerOwner = nullptr;
}

void UFFCameraManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerOwner = Cast<AFireflyPlayerController>(GetOwner());

	CurrentCamera = GetCameraConfig()->GetFirstCamera();
	
	Camera = CastChecked<AFFCameraActor>(GetWorld()->SpawnActor(CurrentCamera->GetClass()));

	PlayerOwner->SetViewTarget(Camera);

	if (CurrentCamera != nullptr)
	{
		Location = CurrentCamera->GetActorLocation();
		Rotation = CurrentCamera->GetActorRotation();
	}

	Camera->SetActorLocation(Location);
	Camera->SetActorRotation(Rotation);
}

const AFFCameraConfig* UFFCameraManager::GetCameraConfig() const
{
	if (CameraConfig == nullptr)
	{
		for (TActorIterator<AFFCameraConfig> It(GetWorld()); It; ++It)
		{
			((UFFCameraManager*)this)->CameraConfig = *It;
			break;
		}
	}

	return CameraConfig;
}

AFFCameraActor* UFFCameraManager::GetCurrentCamera() const
{
	return CurrentCamera;
}


void UFFCameraManager::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	const UFFGameTuning* GameTuning = GetDefaultGameTuning();

	float Delay = GameTuning->SwitchCameraDuration;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (NextCamera != nullptr)
	{
		// Start
		if (CurrentCamera != nullptr)
		{
			LastLocation = Location;
			LastRotation = Rotation;

			PrevCamera = CurrentCamera;
			CurrentCamera = nullptr;
			Timer = Delay;
		}

		// Moving
		else
		{
			Timer -= DeltaTime;

			if (Timer > 0.f)
			{
				// Move
				float alpha = (1.f - Timer / Delay);
				Location = FMath::Lerp(LastLocation, NextCamera->GetActorLocation(), alpha);
				Rotation = FQuat::Slerp(LastRotation.Quaternion(), NextCamera->GetActorRotation().Quaternion(), alpha).Rotator();
			}
			else
			{
				// Finish
				Location = NextCamera->GetActorLocation();
				Rotation = NextCamera->GetActorRotation();
				CurrentCamera = NextCamera;
				NextCamera = nullptr;
			}
		}
	}

	if (Camera != nullptr)
	{
		Camera->SetActorLocation(Location);
		Camera->SetActorRotation(Rotation);
	}
}

void UFFCameraManager::ApplyInput(float DeltaTime, UInputComponent* InputComponent)
{
	if (PlayerOwner == nullptr || PlayerOwner->IsCameraFree() == false)
		return;

	const FFFCameraParam* CurrentCameraParam = GetCameraConfig()->GetCameraParam(CurrentCamera);

	float Speed = (CurrentCameraParam != nullptr ? CurrentCameraParam->Speed : 0.f);

	float Up = InputComponent->GetAxisValue("MoveUp");
	float Right = InputComponent->GetAxisValue("MoveRight");

	FVector Delta(Right * DeltaTime * Speed, -Up * DeltaTime * Speed, 0.f);

	Location += Delta;
}


void UFFCameraManager::JumpPrevCamera()
{
	if (PlayerOwner == nullptr || PlayerOwner->IsCameraFree() == false)
		return;

	if (NextCamera == nullptr)
		NextCamera = GetCameraConfig()->GetCamera(CurrentCamera, EFFDirection::Down);
}

void UFFCameraManager::JumpNextCamera()
{
	if (PlayerOwner == nullptr || PlayerOwner->IsCameraFree() == false)
		return;

	if (NextCamera == nullptr)
		NextCamera = GetCameraConfig()->GetCamera(CurrentCamera, EFFDirection::Up);
}

void UFFCameraManager::JumpToCamera(AFFCameraActor* NewCamera, bool bForce)
{
	if (PlayerOwner == nullptr || (!bForce && PlayerOwner->IsCameraFree() == false))
		return;

	if (NextCamera == nullptr && NewCamera != CurrentCamera)
		NextCamera = NewCamera;
}

void UFFCameraManager::JumpToActorCamera()
{
	JumpToActorCamera(false);
}

void UFFCameraManager::JumpToActorCamera(bool bForce)
{
	if (PlayerOwner == nullptr || (!bForce && PlayerOwner->IsCameraFree() == false))
		return;

	if (PlayerOwner != nullptr)
	{
		AFFActor* Hover = PlayerOwner->GetHoverActor();
		if (Hover != nullptr)
			JumpToCamera(Hover->Camera);
	}
}

void UFFCameraManager::JumpToMainCamera()
{
	JumpToMainCamera(false);
}

void UFFCameraManager::JumpToMainCamera(bool bForce)
{
	if (PlayerOwner == nullptr || (!bForce && PlayerOwner->IsCameraFree() == false))
		return;

	JumpToCamera(GetCameraConfig()->GetFirstCamera(), bForce);
}
