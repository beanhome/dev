// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Components/PrimitiveComponent.h"
#include "DebugRenderSceneProxy.h"
#include "FFSectorDebugComponent.generated.h"

UCLASS()
class UFFSectorDebugComponent : public UPrimitiveComponent
{
	GENERATED_UCLASS_BODY()
	
	friend class FFFSectorDebugProxy;

public:
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);

	//void SetNextPoint(AStyx2PatrolPoint* Next);
	//void OnNextPointMoved();

	void BuildDisplay(FDebugRenderSceneProxy *DebugSceneProxy = nullptr);
	void RebuildDisplay();

	virtual void CreateRenderState_Concurrent() override;
	virtual void DestroyRenderState_Concurrent() override;

private:
	class AFFSector* SectorOwner;
};

class FFFSectorDebugProxy : public FDebugRenderSceneProxy
{
public:
	FFFSectorDebugProxy(const UFFSectorDebugComponent* InComponent, const FString& InViewFlagName);
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;

	//virtual uint32 GetMemoryFootprint(void) const override;
	//uint32 GetAllocatedSize(void) const;

	virtual void RegisterDebugDrawDelgate();
	virtual void UnregisterDebugDrawDelgate();
	virtual void DrawDebugLabels(UCanvas* Canvas, APlayerController*);

private:
	class AFFSector* SectorOwner;
};
