// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/SWActor.h"
#include "SWFighter.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWFighter : public ASWActor
{
	GENERATED_BODY()

		ASWFighter();

public:
	void SetOutline(bool bEnable, int32 iStencilValue = -1);
	void ShowMoveRange(bool bShow);
	void ShowGhost(bool bShow, bool bCollision);
	void MoveGhost(const FVector& Loc);

	void ActivateLimitation(bool bEnable);

	const class ASWGhost* GetGhost() const;
	class ASWGhost* GetGhost();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<FString> FighterMeshesNames;

	UPROPERTY(EditAnywhere)
	FString CloseRangeMeshName;

	UPROPERTY(EditAnywhere)
	FString FarRangeMeshName;

	UPROPERTY(EditAnywhere)
	FString LimitMeshName;

	UPROPERTY()
	TArray<UPrimitiveComponent*> FighterMeshes;

	UPROPERTY()
	UPrimitiveComponent* CloseRangeMesh;

	UPROPERTY()
	UPrimitiveComponent* FarRangeMesh;

	UPROPERTY()
	UPrimitiveComponent* LimitMesh;

	UPROPERTY(Replicated)
	class ASWGhost* Ghost;
};
