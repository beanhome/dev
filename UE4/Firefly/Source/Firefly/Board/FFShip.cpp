// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFShip.h"
#include "Game/FireflyPlayerController.h"
#include "Board/FFSector.h"
#include "UnrealNetwork.h"

FName AFFShip::ShipTextureName("ShipTexture");

AFFShip::AFFShip()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
}

void AFFShip::ClientInitialize_Implementation(int32 Id)
{
	PlayerId = Id;
}

void AFFShip::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CreateMaterialInstance();
}

void AFFShip::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CreateMaterialInstance();
}

void AFFShip::CreateMaterialInstance()
{
	UPrimitiveComponent* PrimitiveComponent = FindComponentByClass<UPrimitiveComponent>();

	if (PrimitiveComponent)
	{
		if (!ShipMaterial)
			ShipMaterial = PrimitiveComponent->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (ShipMaterial)
		ShipMaterial->SetTextureParameterValue(ShipTextureName, ShipTexture);
}

void AFFShip::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		const FName PropertyName(PropertyChangedEvent.Property->GetFName());
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AFFShip, ShipTexture))
		{
			if (ShipMaterial)
			{
				ShipMaterial->SetTextureParameterValue(ShipTextureName, ShipTexture);
			}
		}
	}
}


bool AFFShip::IsSupportedForNetworking() const
{
	return true;
}

void AFFShip::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFShip, PlayerId);
	DOREPLIFETIME(AFFShip, CurrentSector);
}

void AFFShip::SetSector(int32 SectorId)
{
	UWorld* World = Cast<UWorld>(GetOuter());
	if (!World)
		World = GetWorld();

	for (TActorIterator<AFFSector> It(World); It; ++It)
	{
		AFFSector* Sector = *It;

		if (Sector->GetId() == SectorId)
		{
			SetSector(Sector);
			break;
		}
	}
}

void AFFShip::SetSector(const FString& SectorName)
{
	AFFSector* Sector = FindObject<AFFSector>(GetOuter(), *SectorName);

	UWorld* World = Cast<UWorld>(GetOuter());
	if (!World)
		World = GetWorld();

	if (Sector == nullptr)
	{
		for (TActorIterator<AFFSector> It(World); It; ++It)
		{
			if (It->GetName() == SectorName)
			{
				Sector = *It;
				//UE_LOG(Firefly, Log, TEXT("Found Sector %x (%x)"), Sector, Sector->GetOuter());
				break;
			}
		}
	}

	if (Sector != nullptr)
		SetSector(Sector);
}

void AFFShip::SetSector(AFFSector* Sector)
{
	CurrentSector = Sector;

	SetLocation(Sector->GetCenter());
}


void AFFShip::Tick(float DeltaSeconds)
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
