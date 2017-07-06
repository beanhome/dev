// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_MultiChooseInList.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_Card.h"

AFFGameSequence_MultiChooseInList::AFFGameSequence_MultiChooseInList()
{
}

void AFFGameSequence_MultiChooseInList::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_MultiChooseInList, CardList);
}

void AFFGameSequence_MultiChooseInList::SetMax(int32 iMax)
{
	Maximum = iMax;
}

void AFFGameSequence_MultiChooseInList::SetClassList(const TArray<TSubclassOf<class AFFActor>>& List)
{
	check(IsServer());
	ClassList = List;
}

void AFFGameSequence_MultiChooseInList::SetCardList(const TArray<TSubclassOf<class AFFGameSequence_Card>>& List)
{
	check(IsServer());
	CardList = List;
}

void AFFGameSequence_MultiChooseInList::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}


void AFFGameSequence_MultiChooseInList::Start()
{
	Super::Start();

	//if (IsClient() && IsMyTurn())
	if (IsServer())
	{
		ChoiceList = StartSubSequence<AFFGameSequence_ChooseInList>(ChooseListTemplate);
		ChoiceList->SetClassList(ClassList);
		ChoiceList->ChooseInListDelegate.AddDynamic(this, &AFFGameSequence_MultiChooseInList::OnChoiceListSelect);

		ChoosenList = StartSubSequence<AFFGameSequence_ChooseInList>(ChoosenListTemplate);
		ChoosenList->ChooseInListDelegate.AddDynamic(this, &AFFGameSequence_MultiChooseInList::OnChoosenListSelect);
	}
}

void AFFGameSequence_MultiChooseInList::End()
{
	Super::End();
}

void AFFGameSequence_MultiChooseInList::OnChoiceListSelect(int32 id)
{
	if (ChoosenList->GetListCount() < Maximum)
	{
		AFFActor* Card = ChoiceList->RemCard(id);
		ChoosenList->AddCard(Card);
	}
}

void AFFGameSequence_MultiChooseInList::OnChoosenListSelect(int32 id)
{
	AFFActor* Card = ChoosenList->RemCard(id);
	ChoiceList->AddCard(Card);
}

void AFFGameSequence_MultiChooseInList::OnValidate()
{
	Super::OnValidate();

	// Do something
	// ...

	if (IsServer())
	{
		StopSubSequence(ChoiceList);
		StopSubSequence(ChoosenList);
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_MultiChooseInList::OnCancel()
{
	Super::OnCancel();

	if (IsServer())
	{
		StopSubSequence(ChoiceList);
		StopSubSequence(ChoosenList);
		ServerStopCurrentSequence();
	}
}
