// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFCard.h"

FName AFFCard::FrontTextureName("FrontTexture");
FName AFFCard::BackTextureName("BackTexture");

AFFCard::AFFCard()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	PrimaryActorTick.bCanEverTick = true;
}

AFFCard::~AFFCard()
{

}


void AFFCard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateMaterialInstance();
}

void AFFCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CreateMaterialInstance();
}


void AFFCard::CreateMaterialInstance()
{
	UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>();

	if (PrimitiveComponent)
	{
		if (!FrontMaterial)
			FrontMaterial = PrimitiveComponent->CreateAndSetMaterialInstanceDynamic(0);

		if (!BackMaterial)
			BackMaterial = PrimitiveComponent->CreateAndSetMaterialInstanceDynamic(1);
	}

	if (FrontMaterial)
		FrontMaterial->SetTextureParameterValue(FrontTextureName, FrontTexture);

	if (BackMaterial)
		BackMaterial->SetTextureParameterValue(BackTextureName, BackTexture);
}

void AFFCard::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFCard, FrontTexture))
		{
			if (FrontMaterial)
			{
				FrontMaterial->SetTextureParameterValue(FrontTextureName, FrontTexture);
			}
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFCard, BackTexture))
		{
			if (BackMaterial)
			{
				BackMaterial->SetTextureParameterValue(BackTextureName, BackTexture);
			}
		}
	}
}

void AFFCard::Tick(float DeltaSeconds)
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
