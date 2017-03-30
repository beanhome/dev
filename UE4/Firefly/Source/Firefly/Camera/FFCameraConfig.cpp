// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFCameraConfig.h"

AFFCameraConfig::AFFCameraConfig()
{
}

AFFCameraActor* AFFCameraConfig::GetFirstCamera() const
{
	if (Cameras.Num() == 0)
		return nullptr;
	
	return Cameras[0].Camera;
}

const FFFCameraParam* AFFCameraConfig::GetCameraParam(AFFCameraActor* CurCam) const
{
	return Cameras.FindByPredicate([&](const FFFCameraParam& elem) { return (elem.Camera == CurCam); });
}

AFFCameraActor* AFFCameraConfig::GetCamera(AFFCameraActor* Camera, EFFDirection Dir) const
{
	const FFFCameraParam* CameraFound = GetCameraParam(Camera);
	if (CameraFound == nullptr)
		return Camera;

	const FFFCameraTransition* TransitionFound = CameraFound->Transitions.FindByPredicate([&](const FFFCameraTransition& elem) { return (elem.Direction == Dir); });
	if (TransitionFound == nullptr)
		return Camera;

	return TransitionFound->NextCamera;
}


