// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFDiscardPile.h"
#include "Game/GameSequence/FFGameSequence_Card.h"

FName AFFDiscardPile::FrontTextureName("FrontTexture");

AFFDiscardPile::AFFDiscardPile()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
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


void AFFDiscardPile::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFDiscardPile, CardList);
}

class AFFDeck* AFFDiscardPile::GetDeck() const
{
	return Deck;
}

void AFFDiscardPile::SetDeck(class AFFDeck* _Deck)
{
	Deck = _Deck;
}

const TArray<TSubclassOf<class AFFCard>>& AFFDiscardPile::GetCardList() const
{
	return CardList;
}

TArray<TSubclassOf<class AFFActor>> AFFDiscardPile::GetCardListAsActor() const
{
	TArray<TSubclassOf<class AFFActor>> List;

	for (TSubclassOf<class AFFCard> Card : CardList)
		List.Add(Card);

	return List;
}

void AFFDiscardPile::AddCard(TSubclassOf<class AFFCard> CardClass)
{
	CardList.Add(CardClass);

	if (DiscardMaterial)
	{
		AFFCard* LastCard = CardClass.GetDefaultObject();
		if (LastCard)
			DiscardMaterial->SetTextureParameterValue(FrontTextureName, LastCard->FrontTexture);
	}
}

void AFFDiscardPile::RemCard(TSubclassOf<class AFFCard> CardClass)
{
	CardList.Remove(CardClass);

	if (DiscardMaterial)
	{
		AFFCard* LastCard = (CardList.Num() > 0 ? CardList[CardList.Num()-1].GetDefaultObject() : nullptr);
		DiscardMaterial->SetTextureParameterValue(FrontTextureName, (LastCard != nullptr ? LastCard->FrontTexture : nullptr));
	}
}


void AFFDiscardPile::Empty()
{
	CardList.Empty();

	if (DiscardMaterial)
		DiscardMaterial->SetTextureParameterValue(FrontTextureName, DiscardTexture);
}

void AFFDiscardPile::OnRep_CardListChange()
{

}


void AFFDiscardPile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsClient())
	{
		DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, FString::FormatAsNumber(CardList.Num()), nullptr, FColor::White, 0.f);

		/*
		if (MouseOver)
		{
			DrawDebugString(GetWorld(), Center + FVector::UpVector * 20.f, GetName(), nullptr, FColor::White, 0.f);
			DrawDebugBox(GetWorld(), Center, Extent, FColor::White, false);
		}
		*/
	}
}

