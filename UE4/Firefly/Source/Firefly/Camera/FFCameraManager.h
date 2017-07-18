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
	void JumpToMainCamera(bool bForce);
	void JumpToActorCamera();
	void JumpToActorCamera(bool bForce);
	void JumpToCamera(AFFCameraActor* Camera, bool bForce = false);

private:
	AFFCameraConfig* CameraConfig;

	class AFireflyPlayerController* PlayerOwner;

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



