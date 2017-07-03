// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFDeck.h"
#include "FFDiscardPile.h"

FName AFFDeck::BackTextureName("BackTexture");

AFFDeck::AFFDeck()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
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

	Init();
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


void AFFDeck::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFDeck, CardList);
}

const TArray<TSubclassOf<class AFFGameSequence_Card>>& AFFDeck::GetCardList() const
{
	return CardList;
}

class AFFDiscardPile* AFFDeck::GetDiscardPile()
{
	return DiscardPile;
}

void AFFDeck::Init()
{
	CardList = CardListModel;

	/*
	int32 Size = CardList.Num();
	for (int32 i = 0; i < Size; ++i)
		CardList.Swap(i, FMath::RandRange(0, Size - 1));
	*/
}

void AFFDeck::OnRep_CardListChange()
{

}

void AFFDeck::Shuffle()
{
	if (DiscardPile)
	{
		CardList.Append(DiscardPile->GetCardList());
		DiscardPile->Empty();
	}

	int32 Size = CardList.Num();
	for (int32 i = 0; i < Size; ++i)
		CardList.Swap(i, FMath::RandRange(0, Size - 1));
}

TSubclassOf<class AFFGameSequence_Card> AFFDeck::DrawCard()
{
	if (CardList.Num() == 0)
		return nullptr;

	int32 i = CardList.Num() - 1;
	TSubclassOf<class AFFGameSequence_Card> Card = CardList[i];
	CardList.RemoveAt(i);

	return Card;
}

void AFFDeck::Discard(TSubclassOf<class AFFGameSequence_Card> CardClass)
{
	if (DiscardPile)
		DiscardPile->AddCard(CardClass);
}

void AFFDeck::Tick(float DeltaSeconds)
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
