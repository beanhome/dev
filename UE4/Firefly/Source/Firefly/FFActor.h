// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.generated.h"

class AFireflyPlayerController;
class AFFCameraActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFFActorMouseClickDelegate, AFFActor*, ClickedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFFActorMouseEnterDelegate, AFFActor*, EnterActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFFActorMouseLeaveDelegate, AFFActor*, ExitActor);

/** The Ship Board of each player */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFActor : public AActor
{
	GENERATED_BODY()

public:
	AFFActor();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	FVector GetCenter() const;
	FVector GetExtent() const;

	AFireflyPlayerController* GetFFPlayerController() const;

	void SetLocation(const FVector& loc);
	void SetRotation(const FRotator& rot);

	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseClick();

public:
	UPROPERTY()
	FFFActorMouseClickDelegate ActorMouseClickDelegate;

	UPROPERTY()
	FFFActorMouseEnterDelegate ActorMouseEnterDelegate;

	UPROPERTY()
	FFFActorMouseLeaveDelegate ActorMouseLeaveDelegate;

	UPROPERTY(EditAnywhere)
	AFFCameraActor* Camera;

protected:
	FVector Center;
	FVector Extent;

	bool MouseOver;
};
