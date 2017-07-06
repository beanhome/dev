// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_PrimeDiscard.h"

AFFGameSequence_PrimeDiscard::AFFGameSequence_PrimeDiscard()
{
}

void AFFGameSequence_PrimeDiscard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_PrimeDiscard, Deck);
}

void AFFGameSequence_PrimeDiscard::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_PrimeDiscard::Start()
{
	Super::Start();

	check(Deck != nullptr);

	if (IsServer())
	{
		TSubclassOf<class AFFCard> Card;

		for (int32 i = 0; i < 3; ++i)
		{
			Card = Deck->DrawCard();
			Deck->GetDiscardPile()->AddCard(Card);
		}

		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_PrimeDiscard::End()
{
	Super::End();
}

void AFFGameSequence_PrimeDiscard::SetDeck(class AFFDeck* _Deck)
{
	check(IsServer());

	Deck = _Deck;
}
