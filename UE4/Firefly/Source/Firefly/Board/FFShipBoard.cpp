// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFShipBoard.h"
#include "Game/FireflyPlayerController.h"

FName AFFShipBoard::FrontTextureName("FrontTexture");

AFFShipBoard::AFFShipBoard()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFFShipBoard::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateMaterialInstance();
}

void AFFShipBoard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CreateMaterialInstance();
}

void AFFShipBoard::CreateMaterialInstance()
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

void AFFShipBoard::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFShipBoard, FrontTexture))
		{
			if (FrontMaterial)
			{
				FrontMaterial->SetTextureParameterValue(FrontTextureName, FrontTexture);
			}
		}
	}
}


void AFFShipBoard::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MouseOver)
	{
		DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, GetName(), nullptr, FColor::White, 0.f);
		DrawDebugBox(GetWorld(), Center, Extent, FColor::White, false);
	}
}
