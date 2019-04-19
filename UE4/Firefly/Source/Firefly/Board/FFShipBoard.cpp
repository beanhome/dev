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

	MaxCrew = 6;
	MaxShipUpgrade = 2;
}

void AFFShipBoard::ClientInitialize_Implementation(int32 Id, const FFFPlayer& Player)
{
	PlayerId = Id;
	Leader = Player.Leader;
	Engine = Player.Engine;

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

		RefreshCredits(Player.Credits);

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

		CreditsText = FindComponentByClass<UTextRenderComponent>();
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
	DOREPLIFETIME(AFFShipBoard, Crew);
	DOREPLIFETIME(AFFShipBoard, Hand);
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

const TArray<class AFFCrewCard*>& AFFShipBoard::GetCrew() const
{
	return Crew;
}

int32 AFFShipBoard::GetMaxCrew() const
{
	return MaxCrew;
}

void AFFShipBoard::RefreshCredits_Implementation(int32 Credits)
{
	if (IsClient())
	{
		//CreditsText->SetText(FText::AsNumber(Player.Credits));
		CreditsText->SetText(FString::FormatAsNumber(Credits) + TEXT(" $"));
	}
}


bool AFFShipBoard::AddStuff(TSubclassOf<AFFStuff> StuffClass, int32 count)
{
	check(IsServer());

	for (int32 i = 0; i < count; ++i)
	{
		if (AddStuff(StuffClass) == false)
			return false;
	}

	return true;
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
	
	return StockNewStuffs(NewStuff);
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
	
	return Stock();
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

void AFFShipBoard::AddCardToHand(TSubclassOf<class AFFSupplyCard> CardClass)
{
	AFFSupplyCard* Card = GetWorld()->SpawnActor<AFFSupplyCard>(CardClass);
	Hand.Add(Card);
}

void AFFShipBoard::AddCrew(TSubclassOf<class AFFCrewCard> CardClass)
{
	AFFCrewCard* Card = GetWorld()->SpawnActor<AFFCrewCard>(CardClass);
	Crew.Add(Card);
}

void AFFShipBoard::OnRep_SetCrew()
{
	if (IsClient() && GetFFPlayerController())
	{
		AFFShipBoardPlace** Found = ShipBoardPlaces.Find((PlayerId - GetFFPlayerController()->GetId() + ShipBoardPlaces.Num()) % ShipBoardPlaces.Num());
		ShipBoardPlace = (Found != nullptr ? *Found : nullptr);

		for (int32 i = 0; i<Crew.Num(); ++i)
		{
			AFFCrewCard* OneCrew = Crew[i];

			if (OneCrew != nullptr)
			{
				OneCrew->SetLocation(ShipBoardPlace->GetCrewLocation(i+1));
				OneCrew->SetRotation(ShipBoardPlace->GetActorRotation());
				OneCrew->SetActorHiddenInGame(false);
			}
		}
	}
}

void AFFShipBoard::RefreshCargo_Implementation()
{
	if (IsClient())
		Stock();
}

void AFFShipBoard::OnRep_RefreshCargo()
{
	if (IsClient())
		Stock();
}

bool AFFShipBoard::TestCargo(const TArray<class AFFStuff*>& _Stuffs) const
{
	TArray<FFFCargo> _Cargo(Cargo);
	TArray<FFFCargo> _Stash(Stash);

	for (FFFCargo& slot : _Cargo)
	{
		slot.First = nullptr;
		slot.Second = nullptr;
	}

	for (FFFCargo& slot : _Stash)
	{
		slot.First = nullptr;
		slot.Second = nullptr;
	}

	return Stock(_Cargo, _Stash, _Stuffs);
}

bool AFFShipBoard::TestAddCargo(class AFFStuff* _Stuff, int32 iCount) const
{
	TArray<class AFFStuff*> AllStuffs(Stuffs);

	for (int32 i=0 ; i<iCount; ++i)
		AllStuffs.Add(_Stuff);

	return TestCargo(AllStuffs);
}

bool AFFShipBoard::TestAddCargo(const TArray<class AFFStuff*>& _Stuffs) const
{
	TArray<class AFFStuff*> AllStuffs(Stuffs);

	AllStuffs.Append(_Stuffs);

	return TestCargo(AllStuffs);
}

bool AFFShipBoard::Stock(TArray<FFFCargo>& _Cargo, TArray<FFFCargo>& _Stash, const TArray<class AFFStuff*>& _Stuffs) const
{
	TArray<class AFFStuff*> CopyStuffs(_Stuffs);

	CopyStuffs.RemoveAll([&](AFFStuff* elem) { return (elem == nullptr); });
	CopyStuffs.Sort([&](AFFStuff& Lhs, AFFStuff& Rhs) { return ((Lhs).IsSmall() == false && (Rhs).IsSmall()) || ((Lhs).GetName() < (Rhs).GetName()); });

	for (AFFStuff* Stuff : CopyStuffs)
	{
		bool IsPlaced = false;

		TArray<FFFCargo>& First = (Stuff->IsIllegal() ? _Stash : _Cargo);
		TArray<FFFCargo>& Second = (Stuff->IsIllegal() ? _Cargo : _Stash);

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

bool AFFShipBoard::Stock()
{
	return Stock(Cargo, Stash, Stuffs);
}

bool AFFShipBoard::StockNewStuffs(const TArray<class AFFStuff*>& _Stuffs)
{
	if (!TestAddCargo(_Stuffs))
		return false;

	Stuffs.Append(_Stuffs);
	Stock();

	return true;
}

bool AFFShipBoard::StockNewStuffs(class AFFStuff* _Stuff, int32 iCount)
{
	if (!TestAddCargo(_Stuff, iCount))
		return false;

	for (int32 i = 0; i<iCount; ++i)
		Stuffs.Add(_Stuff);

	Stock();

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

void AFFShipBoard::MakeAllCrewDisgruntled()
{
	for (AFFCrewCard* OneCrew : Crew)
	{
		if (OneCrew)
			OneCrew->SetDisgruntled(true);
	}
}

void AFFShipBoard::RemoveAllDisgruntled()
{
	for (AFFCrewCard* OneCrew : Crew)
	{
		if (OneCrew)
			OneCrew->SetDisgruntled(false);
	}
}

