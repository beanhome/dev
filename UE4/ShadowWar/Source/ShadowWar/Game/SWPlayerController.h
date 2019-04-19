// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSPlayerController.h"
#include "SWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWPlayerController : public AGSPlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	void MoveUpInput(float Val);
	void MoveRightInput(float Val);

	bool HasCursorGroundLocation() const;
	FVector GetCursorGroundLocation() const;

	bool HasCursorNavLocation() const;
	FVector GetCursorNavLocation() const;

protected:
	UPROPERTY()
	FHitResult CursorGroundHit;

	UPROPERTY()
	bool bHasCursorNav;

	UPROPERTY()
	FVector CursorNavLocation;
};
