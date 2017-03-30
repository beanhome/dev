// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFDiscardPile.h"

FName AFFDiscardPile::FrontTextureName("FrontTexture");

AFFDiscardPile::AFFDiscardPile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFFDiscardPile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateMaterialInstance();
}

void AFFDiscardPile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CreateMaterialInstance();
}

void AFFDiscardPile::CreateMaterialInstance()
{
	UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>();

	if (PrimitiveComponent)
	{
		if (!DiscardMaterial)
			DiscardMaterial = PrimitiveComponent->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (DiscardMaterial)
		DiscardMaterial->SetTextureParameterValue(FrontTextureName, DiscardTexture);
}

void AFFDiscardPile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFDiscardPile, DiscardTexture))
		{
			if (DiscardMaterial)
			{
				DiscardMaterial->SetTextureParameterValue(FrontTextureName, DiscardTexture);
			}
		}
	}
}

void AFFDiscardPile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MouseOver)
	{
		DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, GetName(), nullptr, FColor::White, 0.f);
		DrawDebugBox(GetWorld(), Center, Extent, FColor::White, false);
	}
}

