// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFDeck.h"

FName AFFDeck::BackTextureName("BackTexture");

AFFDeck::AFFDeck()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFFDeck::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateMaterialInstance();
}

void AFFDeck::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CreateMaterialInstance();
}

void AFFDeck::CreateMaterialInstance()
{
	UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>();

	if (PrimitiveComponent)
	{
		if (!BackMaterial)
			BackMaterial = PrimitiveComponent->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (BackMaterial)
		BackMaterial->SetTextureParameterValue(BackTextureName, BackTexture);
}

void AFFDeck::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFDeck, BackTexture))
		{
			if (BackMaterial)
			{
				BackMaterial->SetTextureParameterValue(BackTextureName, BackTexture);
			}
		}
	}
}

void AFFDeck::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	if (MouseOver)
	{
		DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, GetName(), nullptr, FColor::White, 0.f);
		DrawDebugBox(GetWorld(), Center, Extent, FColor::White, false);
	}
	*/
}
