// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "Cards/FFCard.h"
#include "FFGameSequence_DrawMultiCards.h"
#include "FFGameSequence_MultiChooseInList.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_Card.h"
#include "FFGameSequence_Shuffle.h"

AFFGameSequence_DrawMultiCards::AFFGameSequence_DrawMultiCards()
{
}

void AFFGameSequence_DrawMultiCards::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_DrawMultiCards, Deck);
}

void AFFGameSequence_DrawMultiCards::SetDeck(class AFFDeck* _Deck)
{
	Deck = _Deck;
}

void AFFGameSequence_DrawMultiCards::SetChoosenCount(int32 iCount)
{
	ChoosenCount = iCount;
}

void AFFGameSequence_DrawMultiCards::SetPickCount(int32 iCount)
{
	PickCount = iCount;
}

void AFFGameSequence_DrawMultiCards::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}


void AFFGameSequence_DrawMultiCards::Start()
{
	Super::Start();

	if (IsServer())
	{
		DiscardList = StartSubSequence<AFFGameSequence_MultiChooseInList>(ChooseInDiscardTemplate);
		DiscardList->SetClassList(Deck->GetDiscardPile()->GetCardListAsActor());
		DiscardList->SetMax(ChoosenCount);
		DiscardList->ValidateDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnChooseInDiscardValidate);
		DiscardList->CancelDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnChooseInDiscardCancel);
	}
}

void AFFGameSequence_DrawMultiCards::End()
{
	Super::End();
}

void AFFGameSequence_DrawMultiCards::OnChooseInDiscardValidate()
{
	const TArray<AFFActor*>& ChooseList = DiscardList->GetChoosenList()->GetChooseList();

	for (const AFFActor* FFActor : ChooseList)
	{
		const AFFCard* Card = Cast<AFFCard>(FFActor);
		if (Card != nullptr)
			Deck->GetDiscardPile()->RemCard(Card->GetClass());

		SelectListClass.Add(Card->GetClass());
	}

	StopSubSequence(DiscardList);

	DrawAndPickCard();
}

void AFFGameSequence_DrawMultiCards::DrawAndPickCard()
{
	while (SelectListClass.Num() < ChoosenCount)
	{
		TSubclassOf<class AFFCard> CardClass = Deck->DrawCard();

		if (CardClass != nullptr)
		{
			SelectListClass.Add(CardClass);
		}
		else if (Deck->GetDiscardPile()->IsEmpty() == false)
		{
			// shuffle
			AFFGameSequence_Shuffle* ShuffleSequence = StartSubSequence<AFFGameSequence_Shuffle>();
			ShuffleSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnFinishShuffleDeck);
			ShuffleSequence->SetDeck(Deck);
			return;
		}
		else if (Deck->IsEmpty())
		{
			break;
		}
	}

	SelectList = StartSubSequence<AFFGameSequence_MultiChooseInList>(ChooseInSelectListTemplate);
	SelectList->SetClassList(SelectListClass);
	SelectList->SetMax(PickCount);
	SelectList->ValidateDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnChooseInSelectListValidate);
	SelectList->CancelDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnChooseInSelectListCancel);
}

void AFFGameSequence_DrawMultiCards::OnFinishShuffleDeck(AFFGameSequence* Seq)
{
	DrawAndPickCard();
}


void AFFGameSequence_DrawMultiCards::OnChooseInDiscardCancel()
{
	StopSubSequence(DiscardList);
	ServerStopCurrentSequence();
}

void AFFGameSequence_DrawMultiCards::OnChooseInSelectListValidate()
{
	if (SelectList->GetChoosenList()->GetListCount() <= PickCount)
	{
		const TArray<AFFActor*>& DropList = SelectList->GetChoiceList()->GetChooseList();
		const TArray<AFFActor*>& PickList = SelectList->GetChoosenList()->GetChooseList();
		FFFPlayer& Player = GetPlayingPlayer();
			
		// check cost & creww count
		int32 Cost = 0;
		int32 CrewCount = 0;
		for (const AFFActor* Picked : PickList)
		{
			const AFFSupplyCard* SupplyCard = Cast<AFFSupplyCard>(Picked);
			const AFFCrewCard* CrewCard = Cast<AFFCrewCard>(Picked);

			if (SupplyCard != nullptr)
				Cost += SupplyCard->Cost;

			if (CrewCard != nullptr)
				CrewCount++;
		}

		if (Cost > Player.Credits)
		{
			// Send Error Message
			// ...
			return;
		}

		if (1 + Player.ShipBoard->GetCrew().Num() + CrewCount > Player.ShipBoard->GetMaxCrew())
		{
			// Send Error Message
			// ...
			return;
		}

		ConsumeAction();

		for (const AFFActor* Dropped : DropList)
		{
			Deck->GetDiscardPile()->AddCard(Dropped->GetClass());
		}

		for (const AFFActor* Picked : PickList)
		{
			const AFFSupplyCard* SupplyCard = Cast<AFFSupplyCard>(Picked);
			const AFFCrewCard* CrewCard = Cast<AFFCrewCard>(Picked);

			if (CrewCard)
				Player.ShipBoard->AddCrew(CrewCard->GetClass());

			else if (SupplyCard)
				Player.ShipBoard->AddCardToHand(SupplyCard->GetClass());
		}

		Player.Credits -= Cost;
		Player.ShipBoard->RefreshCredits(Player.Credits);

		StopSubSequence(SelectList);
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_DrawMultiCards::OnChooseInSelectListCancel()
{
	// Do nothing
}
