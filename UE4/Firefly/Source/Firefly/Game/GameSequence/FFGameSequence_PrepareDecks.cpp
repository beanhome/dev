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
	return true;
}

void AFFGameSequence_PrepareDecks::Start()
{
	if (IsServer())
	{
		for (TActorIterator<AFFDeck> It(GetWorld()); It; ++It)
			Decks.Add(*It);

		Index = 0;

		bool res = PrimeDiscardStart();
		if (res)
			return;

		ServerStopCurrentSequence();
	}

	Super::Start();
}

bool AFFGameSequence_PrepareDecks::ShuffleDeckStart()
{
	AFFDeck* Deck = ((Index >= 0 && Index < Decks.Num()) ? Decks[Index] : nullptr);

	if (Deck)
	{
		AFFGameSequence_Shuffle* SuffleSeq = StartSubSequence<AFFGameSequence_Shuffle>();
		SuffleSeq->SetDeck(Deck);
		SuffleSeq->EndDelegate.AddDynamic(this, &AFFGameSequence_PrepareDecks::ShuffleDeckFinish);
		return true;
	}

	return false;
}


void AFFGameSequence_PrepareDecks::ShuffleDeckFinish(AFFGameSequence* Seq)
{
	++Index;

	bool res = ShuffleDeckStart();
	if (res)
		return;
	
	Index = 0;
	res = PrimeDiscardStart();
	if (res)
		return;

	ServerStopCurrentSequence();
}


bool AFFGameSequence_PrepareDecks::PrimeDiscardStart()
{
	AFFDeck* Deck = ((Index >= 0 && Index < Decks.Num()) ? Decks[Index] : nullptr);

	if (Deck)
	{
		AFFGameSequence_PrimeDiscard* SuffleSeq = StartSubSequence<AFFGameSequence_PrimeDiscard>();
		SuffleSeq->SetDeck(Deck);
		SuffleSeq->EndDelegate.AddDynamic(this, &AFFGameSequence_PrepareDecks::PrimeDiscardFinish);
		return true;
	}

	return false;
}

void AFFGameSequence_PrepareDecks::PrimeDiscardFinish(AFFGameSequence* Seq)
{
	++Index;

	bool res = PrimeDiscardStart();
	if (res)
		return;

	ServerStopCurrentSequence();
}

void AFFGameSequence_PrepareDecks::End()
{
	Super::End();
}

