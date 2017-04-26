// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFShipBoard.h"
#include "Cards/Cards/FFLeaderCard.h"
#include "Cards/Cards/FFEngineCard.h"
#include "Game/FireflyPlayerController.h"
#include "UnrealNetwork.h"
#include "Board/FFShipBoardPlace.h"

FName AFFShipBoard::FrontTextureName("FrontTexture");

AFFShipBoard::AFFShipBoard()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
}

void AFFShipBoard::ClientInitialize_Implementation(int32 Id, AFFLeaderCard* _Leader)
{
	PlayerId = Id;
	Leader = _Leader;

	if (GetFFPlayerController())
	{
		AFFShipBoardPlace** Found = ShipBoardPlaces.Find((PlayerId - GetFFPlayerController()->GetId() + ShipBoardPlaces.Num()) % ShipBoardPlaces.Num());
		ShipBoardPlace = (Found != nullptr ? *Found : nullptr);
		
		if (ShipBoardPlace != nullptr)
		{
			SetLocation(ShipBoardPlace->GetActorLocation());
			SetRotation(ShipBoardPlace->GetActorRotation());
			Camera = ShipBoardPlace->Camera;
			Leader->SetLocation(ShipBoardPlace->GetCrewLocation());
			Leader->SetRotation(ShipBoardPlace->GetActorRotation());
			Leader->SetActorHiddenInGame(false);

			Engine = GetWorld()->SpawnActor<AFFEngineCard>(DefaultEngine);
			if (Engine != nullptr)
			{
				Engine->SetLocation(ShipBoardPlace->GetEngineLocation());
				Engine->SetRotation(ShipBoardPlace->GetActorRotation());
				Engine->SetActorHiddenInGame(false);
			}
		}
	}
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

	for (TActorIterator<AFFShipBoardPlace> It(GetWorld()); It; ++It)
	{
		AFFShipBoardPlace* Place = *It;

		const FString& PlaceName = Place->GetName();
		int32 NumberIndex;
		PlaceName.FindLastChar('_', NumberIndex);
		int32 Id = FCString::Atoi(&PlaceName[NumberIndex + 1]);

		ShipBoardPlaces.Add(Id, Place);
		Place->SetActorHiddenInGame(true);
	}
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


bool AFFShipBoard::IsSupportedForNetworking() const
{
	return true;
}

void AFFShipBoard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFShipBoard, PlayerId);
}



void AFFShipBoard::Tick(float DeltaSeconds)
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
