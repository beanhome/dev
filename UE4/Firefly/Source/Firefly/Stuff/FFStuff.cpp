// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFStuff.h"

FName AFFStuff::FrontTextureName("Texture");

AFFStuff::AFFStuff()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
	//PrimaryActorTick.bCanEverTick = true;
}

bool AFFStuff::IsIllegal() const
{
	return Illegal;
}

bool AFFStuff::IsSmall() const
{
	return Small;
}

void AFFStuff::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateMaterialInstance();
}

void AFFStuff::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CreateMaterialInstance();
}


void AFFStuff::CreateMaterialInstance()
{
	UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>();

	if (PrimitiveComponent)
	{
		if (!FrontMaterial)
			FrontMaterial = PrimitiveComponent->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (FrontMaterial)
		FrontMaterial->SetTextureParameterValue(FrontTextureName, FrontTexture);
}

void AFFStuff::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFStuff, FrontTexture))
		{
			if (FrontMaterial)
			{
				FrontMaterial->SetTextureParameterValue(FrontTextureName, FrontTexture);
			}
		}
	}
}

void AFFStuff::Tick(float DeltaSeconds)
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
