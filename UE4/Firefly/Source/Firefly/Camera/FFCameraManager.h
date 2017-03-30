// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Containers/List.h"

#include "FFCameraManager.generated.h"

UCLASS(minimalapi)
class UFFCameraManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UFFCameraManager();

	virtual void BeginPlay() override;

	const AFFCameraConfig* GetCameraConfig() const;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplyInput(float DeltaTime, UInputComponent* InputComponent);

	AFFCameraActor* GetCurrentCamera() const;

	void JumpPrevCamera();
	void JumpNextCamera();
	void JumpToMainCamera();
	void JumpToCamera(AFFCameraActor* Camera);

private:
	AFFCameraConfig* CameraConfig;

	UPROPERTY()
	AFFCameraActor* Camera;

	UPROPERTY()
	AFFCameraActor* CurrentCamera;

	UPROPERTY()
	AFFCameraActor* PrevCamera;

	UPROPERTY()
	AFFCameraActor* NextCamera;

	FVector Location;
	FRotator Rotation;

	FVector LastLocation;
	FRotator LastRotation;

	float Timer;
};



