// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWFighter.h"
#include "SWGhost.h"
#include "Game/SWGameTuning.h"
#include "EngineUtils.h"
#include "UnrealNetwork.h"

ASWFighter::ASWFighter()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bReplicateMovement = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ASWFighter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UPrimitiveComponent*> OutComponents;
	GetComponents(OutComponents);

	for (UPrimitiveComponent* Comp : OutComponents)
	{
		if (FighterMeshesNames.Find(Comp->GetName()) != -1)
			FighterMeshes.Add(Comp);

		if (CloseRangeMeshName == Comp->GetName())
			CloseRangeMesh = Comp;

		if (FarRangeMeshName == Comp->GetName())
			FarRangeMesh = Comp;

		if (LimitMeshName == Comp->GetName())
			LimitMesh = Comp;
	}

	if (CloseRangeMesh != nullptr)
		CloseRangeMesh->SetVisibility(false);

	if (FarRangeMesh != nullptr)
		FarRangeMesh->SetVisibility(false);

	if (LimitMesh != nullptr)
	{
		LimitMesh->SetVisibility(false);
		LimitMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASWFighter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASWFighter, Ghost);
}

void ASWFighter::BeginPlay()
{
	Super::BeginPlay();

	if (IsServer())
	{
		Ghost = GetWorld()->SpawnActor<ASWGhost>(GetDefaultGameTuning()->GhostTemplate);
		if (Ghost != nullptr)
		{
			Ghost->SetActorHiddenInGame(true);
			Ghost->SetFighter(this);
		}
	}
}

const ASWGhost* ASWFighter::GetGhost() const
{
	return Ghost;
}

ASWGhost* ASWFighter::GetGhost()
{
	return Ghost;
}


void ASWFighter::SetOutline(bool bEnable, int32 iStencilValue)
{
	for (UPrimitiveComponent* Comp : FighterMeshes)
	{
		Comp->SetRenderCustomDepth(bEnable);
		if (iStencilValue >= 0)
			Comp->SetCustomDepthStencilValue(iStencilValue);
	}
}

void ASWFighter::ShowMoveRange(bool bEnable)
{
	if (CloseRangeMesh != nullptr)
		CloseRangeMesh->SetVisibility(bEnable);

	if (FarRangeMesh != nullptr)
		FarRangeMesh->SetVisibility(bEnable);
}

void ASWFighter::ShowGhost(bool bShow, bool bCollision)
{
	if (Ghost != nullptr)
	{
		Ghost->SetActorHiddenInGame(!bShow);
		Ghost->SetActorEnableCollision(bCollision);
	}
}

void ASWFighter::MoveGhost(const FVector& Loc)
{
	if (Ghost != nullptr)
	{
		Ghost->SetActorLocation(Loc);
	}
}

void ASWFighter::ActivateLimitation(bool bEnable)
{
	if (LimitMesh)
		LimitMesh->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}



void ASWFighter::Tick(float DeltaSeconds)
{
	if (Ghost != nullptr && Ghost->bHidden == false)
	{
		if ((GetActorLocation() - Ghost->GetActorLocation()).Size2D() > 60.f)
			DrawDebugLine(GetWorld(), GetActorLocation(), Ghost->GetActorLocation(), FColor::Red);
	}
}
