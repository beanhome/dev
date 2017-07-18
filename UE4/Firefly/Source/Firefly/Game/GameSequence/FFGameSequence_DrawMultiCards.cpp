// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "Cards/FFCard.h"
#include "FFGameSequence_DrawMultiCards.h"
#include "FFGameSequence_MultiChooseInList.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_Card.h"

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

	TArray<TSubclassOf<AFFActor> > SelectListClass;

	for (const AFFActor* FFActor : ChooseList)
	{
		const AFFCard* Card = Cast<AFFCard>(FFActor);
		if (Card != nullptr)
			Deck->GetDiscardPile()->RemCard(Card->GetClass());

		SelectListClass.Add(Card->GetClass());
	}

	while (SelectListClass.Num() < ChoosenCount)
	{
		SelectListClass.Add(Deck->DrawCard());
	}

	StopSubSequence(DiscardList);

	SelectList = StartSubSequence<AFFGameSequence_MultiChooseInList>(ChooseInSelectListTemplate);
	SelectList->SetClassList(SelectListClass);
	SelectList->SetMax(PickCount);
	SelectList->ValidateDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnChooseInSelectListValidate);
	SelectList->CancelDelegate.AddDynamic(this, &AFFGameSequence_DrawMultiCards::OnChooseInSelectListCancel);

}

void AFFGameSequence_DrawMultiCards::OnChooseInDiscardCancel()
{
	StopSubSequence(DiscardList);
	ServerStopCurrentSequence();
}

void AFFGameSequence_DrawMultiCards::OnChooseInSelectListValidate()
{
	if (SelectList->GetChoosenList()->GetListCount() == PickCount)
	{
		const TArray<AFFActor*>& DropList = SelectList->GetChoiceList()->GetChooseList();
		for (const AFFActor* Dropped : DropList)
		{
			Deck->GetDiscardPile()->AddCard(Dropped->GetClass());
		}

		const TArray<AFFActor*>& PickList = SelectList->GetChoosenList()->GetChooseList();
		for (const AFFActor* Picked : PickList)
		{
			const FFFPlayer& Player = GetPlayingPlayer();
			
			const AFFSupplyCard* SupplyCard = Cast<AFFSupplyCard>(Picked);
			const AFFCrewCard* CrewCard = Cast<AFFCrewCard>(Picked);

			if (CrewCard)
				Player.ShipBoard->AddCrew(CrewCard->GetClass());

			else if (SupplyCard)
				Player.ShipBoard->AddCardToHand(SupplyCard->GetClass());
		}

		StopSubSequence(SelectList);
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_DrawMultiCards::OnChooseInSelectListCancel()
{
	// Do nothing
}
