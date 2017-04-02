// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFSectorDebugComponent.h"
#include "FFSector.h"

#include "Debug/DebugDrawService.h"
//#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "EngineGlobals.h"


UFFSectorDebugComponent::UFFSectorDebugComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, SectorOwner(nullptr)
{
	SectorOwner = (GetOwner() != nullptr ? CastChecked<class AFFSector>(GetOwner()) : nullptr);
}

FPrimitiveSceneProxy* UFFSectorDebugComponent::CreateSceneProxy()
{
	FFFSectorDebugProxy* DebugSceneProxy = new FFFSectorDebugProxy(this, TEXT("StaticMeshes"));
	BuildDisplay(DebugSceneProxy);
	//DebugSceneProxy->DrawType = FDebugRenderSceneProxy::SolidAndWireMeshes;
	return DebugSceneProxy;
}

FBoxSphereBounds UFFSectorDebugComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBoxSphereBounds NewBounds;
	if (SectorOwner)
	{
		NewBounds.Origin = SectorOwner->Center;
		NewBounds.BoxExtent = SectorOwner->Extent * 2.f;
	}
	return NewBounds;
}

void UFFSectorDebugComponent::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)
{
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);
	RebuildDisplay();
}

/*
void UFFSectorDebugComponent::SetNextPoint(AStyx2PatrolPoint* Next)
{
	NextPoint = Next;
	RebuildDisplay();
}

void UFFSectorDebugComponent::OnNextPointMoved()
{
	RebuildDisplay();
}
*/

void UFFSectorDebugComponent::BuildDisplay(FDebugRenderSceneProxy *DebugSceneProxy)
{
	if (!DebugSceneProxy && !SceneProxy)
		return;

	if (!DebugSceneProxy)
		DebugSceneProxy = static_cast<FDebugRenderSceneProxy*>(SceneProxy);

	DebugSceneProxy->Lines.Empty();
	DebugSceneProxy->Texts.Empty();

	if (SectorOwner)
	{
		for (AFFSector* Link : SectorOwner->Links)
		{
			if (Link != nullptr)
			{
				DebugSceneProxy->Lines.Add(FDebugRenderSceneProxy::FDebugLine(SectorOwner->Center, Link->Center, FColor::White));
				DebugSceneProxy->Texts.Add(FDebugRenderSceneProxy::FText3d(*Link->GetName(), Link->Center, FColor::Green));
			}
		}
	}
}

void UFFSectorDebugComponent::RebuildDisplay()
{
	BuildDisplay();
	MarkRenderStateDirty();
}


void UFFSectorDebugComponent::CreateRenderState_Concurrent()
{
	Super::CreateRenderState_Concurrent();

#if WITH_EDITOR
	if (SceneProxy)
	{
		static_cast<FFFSectorDebugProxy*>(SceneProxy)->RegisterDebugDrawDelgate();
	}
#endif
}

void UFFSectorDebugComponent::DestroyRenderState_Concurrent()
{
#if WITH_EDITOR
	if (SceneProxy)
	{
		static_cast<FFFSectorDebugProxy*>(SceneProxy)->UnregisterDebugDrawDelgate();
	}
#endif

	Super::DestroyRenderState_Concurrent();
}


FFFSectorDebugProxy::FFFSectorDebugProxy(const UFFSectorDebugComponent* InComponent, const FString& InViewFlagName)
: FDebugRenderSceneProxy(InComponent)
{
	ViewFlagName = InViewFlagName;

	SectorOwner = InComponent->SectorOwner;
}

FPrimitiveViewRelevance FFFSectorDebugProxy::GetViewRelevance(const FSceneView* View) const
{
	FPrimitiveViewRelevance Result;
	//Result.bDrawRelevance = IsShown(View);
	Result.bDrawRelevance = IsShown(View) && IsSelected();
	Result.bShadowRelevance = IsShadowCast(View);
	Result.bDynamicRelevance = true;
	Result.bEditorPrimitiveRelevance = true;
	Result.bRenderCustomDepth = ShouldRenderCustomDepth();
	Result.bRenderInMainPass = ShouldRenderInMainPass();
	return Result;
}


void FFFSectorDebugProxy::RegisterDebugDrawDelgate()
{
	DebugTextDrawingDelegate = FDebugDrawDelegate::CreateRaw(this, &FFFSectorDebugProxy::DrawDebugLabels);
	DebugTextDrawingDelegateHandle = UDebugDrawService::Register(*ViewFlagName, DebugTextDrawingDelegate);
}

void FFFSectorDebugProxy::UnregisterDebugDrawDelgate()
{
	if (DebugTextDrawingDelegate.IsBound())
	{
		UDebugDrawService::Unregister(DebugTextDrawingDelegateHandle);
	}
}

void FFFSectorDebugProxy::DrawDebugLabels(UCanvas* Canvas, APlayerController* Player)
{
	if (!SectorOwner || SectorOwner->IsSelected() == false)
		return;

	const FColor OldDrawColor = Canvas->DrawColor;
	const FFontRenderInfo FontRenderInfo = Canvas->CreateFontRenderInfo(true, false);
	const FFontRenderInfo FontRenderInfoWithShadow = Canvas->CreateFontRenderInfo(true, true);

	Canvas->SetDrawColor(FColor::White);

	UFont* RenderFont = GEngine->GetSmallFont();

	const FSceneView* View = Canvas->SceneView;
	for (auto It = Texts.CreateConstIterator(); It; ++It)
	{
		if (PointInView(It->Location, View))
		{
			const FVector ScreenLoc = Canvas->Project(It->Location);
			const FFontRenderInfo& FontInfo = TextWithoutShadowDistance >= 0 ? (PointInRange(It->Location, View, TextWithoutShadowDistance) ? FontRenderInfoWithShadow : FontRenderInfo) : FontRenderInfo;
			Canvas->DrawText(RenderFont, It->Text, ScreenLoc.X, ScreenLoc.Y, 1, 1, FontInfo);
		}
	}

	Canvas->SetDrawColor(OldDrawColor);
}

/*
uint32 FFFSectorDebugProxy::GetMemoryFootprint(void) const
{
	return sizeof(*this) + GetAllocatedSize();
}

uint32 FFFSectorDebugProxy::GetAllocatedSize(void) const
{
	return FDebugRenderSceneProxy::GetAllocatedSize();
}
*/
