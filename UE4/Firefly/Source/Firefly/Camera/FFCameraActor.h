// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Camera/CameraActor.h"
#include "FFCameraActor.generated.h"

UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AFFCameraActor();

public:
	UPROPERTY(EditAnywhere)
	FVector ExtentMove;

	UPROPERTY(EditAnywhere)
	float Speed;
};
