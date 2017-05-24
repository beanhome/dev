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
	class AFFDeck* GetDeck() const;

	void HighLight(bool bEnable);

#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif

	class UStaticMeshComponent* GetStaticMeshComponent() const;
	void CreateMaterialInstance();

	virtual void OnMouseEnter() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseClick() override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<AFFSector*> Links;

	UPROPERTY()
	UFFSectorDebugComponent* DebugComponent;

private:
	UPROPERTY()
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* SectorMaterial;

	UPROPERTY(EditAnywhere)
	int32 Id;

	UPROPERTY(EditAnywhere)
	class AFFDeck* Deck;

	int32 HighLightCount;

};
