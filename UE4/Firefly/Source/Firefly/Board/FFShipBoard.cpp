// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFShipBoard.h"
#include "Cards/Cards/FFLeaderCard.h"
#include "Cards/Cards/FFEngineCard.h"
#include "Game/FireflyPlayerController.h"
#include "UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "Board/FFShipBoardPlace.h"
#include "Stuff/FFStuff.h"


bool FFFCargo::AddStuff(AFFStuff* stuff)
{
	if (First == nullptr)
	{
		First = stuff;
		stuff->SetActorLocation(stuff->IsSmall() ? HalfLoc0->GetComponentLocation() : BigLoc->GetComponentLocation());
		stuff->SetActorHiddenInGame(false);
		return true;
	}
	else if (stuff->IsSmall() && First->IsSmall() && Second == nullptr)
	{
		Second = stuff;
		stuff->SetActorLocation(HalfLoc1->GetComponentLocation());
		stuff->SetActorHiddenInGame(false);
		return true;
	}

	return false;
}

bool FFFCargo::RemStuff(AFFStuff* stuff)
{
	if (stuff == Second)
	{
		Second = nullptr;
		return true;
	}
	else if (stuff == First && Second != nullptr)
	{
		First = Second;
		Second = nullptr;
		First->SetActorLocation(HalfLoc0->GetComponentLocation());
		return true;
	}

	return false;
}

FName AFFShipBoard::FrontTextureName("FrontTexture");

AFFShipBoard::AFFShipBoard()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
}

void AFFShipBoard::ClientInitialize_Implementation(int32 Id, AFFLeaderCard* _Leader, AFFEngineCard* _Engine)
{
	PlayerId = Id;
	Leader = _Leader;
	Engine = _Engine;

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

			if (Engine != nullptr)
			{
				Engine->SetLocation(ShipBoardPlace->GetEngineLocation());
				Engine->SetRotation(ShipBoardPlace->GetActorRotation());
				Engine->SetActorHiddenInGame(false);
			}
		}
	}
}

void AFFShipBoard::OnRep_SetEngine()
{
	if (GetFFPlayerController())
	{
		AFFShipBoardPlace** Found = ShipBoardPlaces.Find((PlayerId - GetFFPlayerController()->GetId() + ShipBoardPlaces.Num()) % ShipBoardPlaces.Num());
		ShipBoardPlace = (Found != nullptr ? *Found : nullptr);

		if (Engine != nullptr)
		{
			Engine->SetLocation(ShipBoardPlace->GetEngineLocation());
			Engine->SetRotation(ShipBoardPlace->GetActorRotation());
			Engine->SetActorHiddenInGame(false);
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

	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject) && GetWorld()->IsGameWorld())
	{
		TArray<UStaticMeshComponent*> OutComponents;
		GetComponents(OutComponents);

		for (UStaticMeshComponent* Comp : OutComponents)
		{
			FString CompName = Comp->GetName();
			bool bIsCargo = (CompName.Find("Cargo") != INDEX_NONE);
			bool bIsStash = (CompName.Find("Stash") != INDEX_NONE);

			if (bIsCargo || bIsStash)
			{
				FString strId = CompName.Mid(5, 2);
				FString strSubId = CompName.RightChop(7);

				if (strSubId.IsEmpty())
				{
					FFFCargo _Cargo;
					_Cargo.BigLoc = Comp;
					_Cargo.HalfLoc0 = nullptr;
					_Cargo.HalfLoc1 = nullptr;

					(bIsCargo ? Cargo : Stash).Add(_Cargo);
				}
				else
				{
					FString ParentName = CompName.Left(7);
					FFFCargo* _Cargo = (bIsCargo ? Cargo : Stash).FindByPredicate([&](const FFFCargo& elem) { return (elem.BigLoc != nullptr && elem.BigLoc->GetName() == ParentName); });
					if (_Cargo != nullptr)
					{
						(strSubId[0] == '0' ? _Cargo->HalfLoc0 : _Cargo->HalfLoc1) = Comp;
					}
				}
			}
		}

		for (FFFCargo& Slot : Cargo)
		{
			if (Slot.BigLoc != nullptr)
				Slot.BigLoc->SetHiddenInGame(true);
			if (Slot.HalfLoc0 != nullptr)
				Slot.HalfLoc0->SetHiddenInGame(true);
			if (Slot.HalfLoc1 != nullptr)
				Slot.HalfLoc1->SetHiddenInGame(true);
		}

		for (FFFCargo& Slot : Stash)
		{
			if (Slot.BigLoc != nullptr)
				Slot.BigLoc->SetHiddenInGame(true);
			if (Slot.HalfLoc0 != nullptr)
				Slot.HalfLoc0->SetHiddenInGame(true);
			if (Slot.HalfLoc1 != nullptr)
				Slot.HalfLoc1->SetHiddenInGame(true);
		}
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
	DOREPLIFETIME(AFFShipBoard, Engine);
	DOREPLIFETIME(AFFShipBoard, Stuffs);
}

class AFFEngineCard* AFFShipBoard::GetEngine() const
{
	check(Engine != nullptr);
	return Engine;
}

void AFFShipBoard::InitCargo()
{
	check(IsServer());

	for (TSubclassOf<class AFFStuff>& StuffClass : DefaultStuffs)
	{
		AddStuff(StuffClass);
	}
}

bool AFFShipBoard::AddStuff(TSubclassOf<AFFStuff> StuffClass)
{
	check(IsServer());
	
	AFFStuff* Stuff = GetWorld()->SpawnActor<AFFStuff>(StuffClass);

	if (AddStuff(Stuff) == false)
	{
		Stuff->Destroy();
		return false;
	}

	return true;
}

bool AFFShipBoard::AddStuff(class AFFStuff* NewStuff)
{
	check(IsServer());
	
	Stuffs.Add(NewStuff);

	if (CheckAndRefreshCargo() == false)
	{
		Stuffs.Remove(NewStuff);
		return false;
	}

	return true;
}

bool AFFShipBoard::RemStuff(TSubclassOf<AFFStuff> StuffClass)
{
	check(IsServer());
	
	class AFFStuff** Stuff = Stuffs.FindByPredicate([&](const AFFStuff* elem) { return (elem != nullptr && elem->GetClass() == StuffClass); });

	return RemStuff(*Stuff);
}

bool AFFShipBoard::RemStuff(class AFFStuff* Stuff)
{
	check(IsServer());

	Stuffs.Remove(Stuff);

	Stuff->Destroy();
	
	return CheckAndRefreshCargo();
}

bool AFFShipBoard::HasStuff(TSubclassOf<class AFFStuff> StuffClass, int32 nb)
{
	int32 count = 0;
	for (class AFFStuff* Stuff : Stuffs)
	{
		if (Stuff != nullptr && Stuff->GetClass() == StuffClass)
			count++;
	}

	nb = FMath::Max(nb, 1);

	return count >= nb;
}

void AFFShipBoard::RefreshCargo_Implementation()
{
	if (IsClient())
		CheckAndRefreshCargo();
}

void AFFShipBoard::OnRep_RefreshCargo()
{
	if (IsClient())
		CheckAndRefreshCargo();
}

bool AFFShipBoard::CheckAndRefreshCargo()
{
	for (FFFCargo& slot : Cargo)
	{
		slot.First = nullptr;
		slot.Second = nullptr;
	}

	for (FFFCargo& slot : Stash)
	{
		slot.First = nullptr;
		slot.Second = nullptr;
	}

	TArray<class AFFStuff*> CopyStuffs(Stuffs);

	CopyStuffs.RemoveAll([&](AFFStuff* elem) { return (elem == nullptr); });
	CopyStuffs.Sort([&](AFFStuff& Lhs, AFFStuff& Rhs) { return ((Lhs).IsSmall() == false && (Rhs).IsSmall()) || ((Lhs).GetName() < (Rhs).GetName()); });

	for (AFFStuff* Stuff : CopyStuffs)
	{
		bool IsPlaced = false;

		TArray<FFFCargo>& First = (Stuff->IsIllegal() ? Stash : Cargo);
		TArray<FFFCargo>& Second = (Stuff->IsIllegal() ? Cargo : Stash);

		for (FFFCargo& slot : First)
		{
			if (slot.AddStuff(Stuff))
			{
				IsPlaced = true;
				break;
			}
		}

		if (IsPlaced)
			continue;

		for (FFFCargo& slot : Second)
		{
			if (slot.AddStuff(Stuff))
			{
				IsPlaced = true;
				break;
			}
		}

		if (IsPlaced == false)
			return false;
	}

	return true;
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
