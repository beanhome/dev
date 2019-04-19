// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWActor.h"

void ASWActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UPrimitiveComponent*> OutComponents;
	GetComponents(OutComponents);

	for (UPrimitiveComponent* Comp : OutComponents)
	{
		if (OutlineMeshesNames.Find(Comp->GetName()) != -1)
			OutlineMeshes.Add(Comp);
	}
}

void ASWActor::SetOutline(bool bEnable, int32 iStencilValue)
{
	for (UPrimitiveComponent* Comp : OutlineMeshes)
	{
		Comp->SetRenderCustomDepth(bEnable);
		if (iStencilValue >= 0)
			Comp->SetCustomDepthStencilValue(iStencilValue);
	}
}


