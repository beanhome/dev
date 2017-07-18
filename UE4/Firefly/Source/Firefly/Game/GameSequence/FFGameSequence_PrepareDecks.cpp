// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_PrepareDecks.h"
#include "FFGameSequence_PrimeDiscard.h"
#include "Cards/FFDeck.h"
#include "Cards/FFDiscardPile.h"

AFFGameSequence_PrepareDecks::AFFGameSequence_PrepareDecks()
{
}

void AFFGameSequence_PrepareDecks::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AFFGameSequence_PrepareDecks::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

bool AFFGameSequence_PrepareDecks::IsCameraFree() const
{
	return false;
}

AFFDeck* AFFGameSequence_PrepareDecks::GetFirstDeckToShuffle()
{
	Index = -1;
	return GetNextDeckToShuffle();
}

AFFDeck* AFFGameSequence_PrepareDecks::GetNextDeckToShuffle()
{
	while (true)
	{
		Index++;

		if (Index < 0 || Index >= Decks.Num())
			return nullptr;

		AFFDeck* Deck = Decks[Index];

		if (Deck == nullptr)
			continue;

		if (Deck->bShuffle == false)
			continue;

		return Deck;
	}
}

AFFDeck* AFFGameSequence_PrepareDecks::GetFirstDeckToPrimeDiscard()
{
	Index = -1;
	return GetNextDeckToPrimeDiscard();
}

AFFDeck* AFFGameSequence_PrepareDecks::GetNextDeckToPrimeDiscard()
{
	while (true)
	{
		Index++;

		if (Index < 0 || Index >= Decks.Num())
			return nullptr;

		AFFDeck* Deck = Decks[Index];

		if (Deck == nullptr)
			continue;

		if (Deck->bPrimeDiscard == false)
			continue;

		return Deck;
	}
}


void AFFGameSequence_PrepareDecks::Start()
{
	if (IsServer())
	{
		for (TActorIterator<AFFDeck> It(GetWorld()); It; ++It)
			Decks.Add(*It);

		AFFDeck* Deck = GetFirstDeckToShuffle();

		if (Deck != nullptr)
			ShuffleDeckStart(Deck);
		else
			ServerStopCurrentSequence();
	}
	else
	{
		GetFFPlayerController()->JumpToMainCamera(true);
	}

	Super::Start();
}

void AFFGameSequence_PrepareDecks::ShuffleDeckStart(AFFDeck* Deck)
{
	AFFGameSequence_Shuffle* ShuffleSeq = StartSubSequence<AFFGameSequence_Shuffle>();
	ShuffleSeq->SetDeck(Deck);
	ShuffleSeq->EndDelegate.AddDynamic(this, &AFFGameSequence_PrepareDecks::ShuffleDeckFinish);
}


void AFFGameSequence_PrepareDecks::ShuffleDeckFinish(AFFGameSequence* Seq)
{
	AFFDeck* Deck = GetNextDeckToShuffle();

	if (Deck != nullptr)
	{
		ShuffleDeckStart(Deck);
		return;
	}

	Deck = GetFirstDeckToPrimeDiscard();

	if (Deck != nullptr)
	{
		PrimeDiscardStart(Deck);
		return;
	}
	
	ServerStopCurrentSequence();
}


void AFFGameSequence_PrepareDecks::PrimeDiscardStart(AFFDeck* Deck)
{
	AFFGameSequence_PrimeDiscard* ShuffleSeq = StartSubSequence<AFFGameSequence_PrimeDiscard>();
	ShuffleSeq->SetDeck(Deck);
	ShuffleSeq->EndDelegate.AddDynamic(this, &AFFGameSequence_PrepareDecks::PrimeDiscardFinish);
}

void AFFGameSequence_PrepareDecks::PrimeDiscardFinish(AFFGameSequence* Seq)
{
	AFFDeck* Deck = GetNextDeckToPrimeDiscard();

	if (Deck != nullptr)
	{
		PrimeDiscardStart(Deck);
	}
	else
	{
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_PrepareDecks::End()
{
	Super::End();
}

