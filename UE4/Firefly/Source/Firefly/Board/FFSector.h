// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"

#include "Game/FFPathFinder.h"

#include "FFSector.generated.h"

class AFireflyPlayerController;
class AFFCameraActor;

/** A block that can be clicked */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFSector : public AFFActor
{
	friend class UFFSectorDebugComponent;

	GENERATED_BODY()

public:
	AFFSector();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	int32 GetId() const;

	const TArray<AFFSector*>& GetLinks() const;

#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif

	class UStaticMeshComponent* GetStaticMeshComponent() const;

	virtual void OnMouseEnter() override;
	virtual void OnMouseExit() override;
	virtual void OnMouseClick() override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<AFFSector*> Links;

	UPROPERTY()
	UFFSectorDebugComponent* DebugComponent;

private:
	UPROPERTY()
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	int32 Id;

	UPROPERTY()
	class UFFPathFinder* PathFinder;

	FFFPath Path;
};
