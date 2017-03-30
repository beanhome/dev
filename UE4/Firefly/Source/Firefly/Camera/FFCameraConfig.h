// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFCameraConfig.generated.h"

UENUM()
enum class EFFDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};

USTRUCT()
struct FFFCameraTransition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EFFDirection Direction;

	UPROPERTY(EditAnywhere)
	AFFCameraActor* NextCamera;
};

USTRUCT()
struct FFFCameraParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	AFFCameraActor* Camera;

	UPROPERTY(EditAnywhere)
	FVector ExtentMove;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	TArray<FFFCameraTransition> Transitions;
};

UCLASS(ClassGroup = "Firefly")
class AFFCameraConfig : public AActor
{
	GENERATED_BODY()

public:
	AFFCameraConfig();

	AFFCameraActor* GetFirstCamera() const;
	AFFCameraActor* GetCamera(AFFCameraActor* CurCam, EFFDirection Dir) const;
	
	const FFFCameraParam* GetCameraParam(AFFCameraActor* CurCam) const;

public:
	UPROPERTY(EditAnywhere)
	TArray<FFFCameraParam> Cameras;
};
