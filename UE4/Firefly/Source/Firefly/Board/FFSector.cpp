// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFSector.h"
#include "FFSectorDebugComponent.h"

#include "FireflyGameMode.h"
#include "Game/FireflyPlayerController.h"
#include "Game/FFPlayerInfo.h"
//#include "Game/FFPathFinder.h"
#include "FFGameState.h"

#include "MessageLog.h"
#include "UObjectToken.h"
#include "MapErrors.h"

#define LOCTEXT_NAMESPACE "FFSector"

AFFSector::AFFSector()
: DebugComponent(nullptr)
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent0"));
	StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	StaticMeshComponent->Mobility = EComponentMobility::Static;
	StaticMeshComponent->bGenerateOverlapEvents = false;

	RootComponent = StaticMeshComponent;

	PrimaryActorTick.bCanEverTick = true;
}

UStaticMeshComponent* AFFSector::GetStaticMeshComponent() const
{
	return StaticMeshComponent;
}

int32 AFFSector::GetId() const
{
	return Id;
}

const TArray<AFFSector*>& AFFSector::GetLinks() const
{
	return Links;
}

void AFFSector::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/*
	const FString& Name = GetName();

	if (Name[0] == 'B')
		Id = 32;
	else if (Name[0] == 'R')
		Id = 106;
	else
		Id = 0;

	Id += FCString::Atoi(&Name[1]) -1;
	*/

	/*
	TArray<struct FOverlapResult> OutOverlaps;
	GetWorld()->OverlapMultiByChannel(OutOverlaps, Center, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, FCollisionShape::MakeBox(Extent * 1.2f));

	Links.Empty();
	for (FOverlapResult& Result : OutOverlaps)
	{
		AFFSector* Sector = Cast<AFFSector>(Result.GetActor());
		if (Sector != nullptr && Sector != this)
			Links.AddUnique(Sector);
	}
	*/

	DebugComponent = NewObject<UFFSectorDebugComponent>(this, TEXT("DebugSector"));
	DebugComponent->AttachToComponent(GetStaticMeshComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	DebugComponent->RegisterComponent();
}

void AFFSector::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DebugComponent->RebuildDisplay();
}

void AFFSector::BeginPlay()
{
	Super::BeginPlay();

	DebugComponent->RebuildDisplay();

	SetActorHiddenInGame(true);
}


#if WITH_EDITOR
void AFFSector::CheckForErrors()
{
	Super::CheckForErrors();

	for (AFFSector* Neigh : Links)
	{
		if (Neigh->Links.Contains(this) == false)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("SectorName"), FText::FromString(GetName()));
			Arguments.Add(TEXT("OtherName"), FText::FromString(Neigh->GetName()));
			FMessageLog("MapCheck").Warning()
				->AddToken(FUObjectToken::Create(this))
				->AddToken(FUObjectToken::Create(Neigh))
				->AddToken(FTextToken::Create(FText::Format(LOCTEXT("MapCheck_Message_FFsector_BadLink", "{SectorName}::{OtherName} Unidirectional link"), Arguments)));
		}
	}
}
#endif	// WITH_EDITOR


void AFFSector::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	if (MouseOver)
	{
		DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, GetName(), nullptr, FColor::White, 0.f);
		DrawDebugBox(GetWorld(), Center, Extent, FColor::White, false);
	}
	*/

	/*
	DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, GetName());

	for (AFFSector* Neigh : Links)
		DrawDebugLine(GetWorld(), Center, Neigh->Center, FColor::White, false);
		*/

	/*
	if (MouseOver)
	{
		int i = 0;
		for (const FFFPathNode& Node : Path.Path)
		{
			DrawDebugString(GetWorld(), Node.Sector->GetCenter() - FVector(0.f, 50.f, 0.f), FString::Printf(TEXT("%d"), Path.Path.Num() - i - 1), nullptr, FColor::White, 0.f);
			i++;

			if (Node.Previous && Node.Sector)
				DrawDebugLine(GetWorld(), Node.Previous->GetCenter(), Node.Sector->GetCenter(), FColor::White, false, 0.f);
		}
	}
	*/
}

void AFFSector::OnMouseEnter()
{
	Super::OnMouseEnter();
}

void AFFSector::OnMouseLeave()
{
	Super::OnMouseLeave();
}

void AFFSector::OnMouseClick()
{
	Super::OnMouseClick();

	DebugComponent->RebuildDisplay();
}
