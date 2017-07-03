// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Shuffle.h"

AFFGameSequence_Shuffle::AFFGameSequence_Shuffle()
{
}

void AFFGameSequence_Shuffle::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_Shuffle, Deck);
}

void AFFGameSequence_Shuffle::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_Shuffle::Start()
{
	Super::Start();

	check(Deck != nullptr);

	if (IsServer())
	{
		Deck->Shuffle();
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_Shuffle::End()
{
	Super::End();
}

void AFFGameSequence_Shuffle::ShuffleDeck(class AFFDeck* _Deck)
{
	check(IsServer());

	Deck = _Deck;
}
