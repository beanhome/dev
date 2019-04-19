// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "GSActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGSActorMouseClickDelegate, AGSActor*, ClickedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGSActorMouseEnterDelegate, AGSActor*, EnterActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGSActorMouseLeaveDelegate, AGSActor*, ExitActor);

/**  */
UCLASS(Blueprintable)
class GAMESEQUENCE_API AGSActor : public AActor
{
	GENERATED_BODY()

public:
	AGSActor();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	class AGSPlayerController* GetGSPlayerController() const;

	void SetLocation(const FVector& loc);
	void SetRotation(const FRotator& rot);

	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseClick();

	bool IsServer() const;
	bool IsClient() const;

public:
	UPROPERTY()
	FGSActorMouseClickDelegate ActorMouseClickDelegate;

	UPROPERTY()
	FGSActorMouseEnterDelegate ActorMouseEnterDelegate;

	UPROPERTY()
	FGSActorMouseLeaveDelegate ActorMouseLeaveDelegate;

protected:
	bool MouseOver;
};
