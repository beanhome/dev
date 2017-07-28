// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_VisitDiscard.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_Card.h"

AFFGameSequence_VisitDiscard::AFFGameSequence_VisitDiscard()
{
}

void AFFGameSequence_VisitDiscard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_VisitDiscard, Discard);
}

void AFFGameSequence_VisitDiscard::SetDiscard(class AFFDiscardPile* _Discard)
{
	Discard = _Discard;
}


void AFFGameSequence_VisitDiscard::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}


void AFFGameSequence_VisitDiscard::Start()
{
	Super::Start();

	if (IsServer())
	{
		ChoiceList = StartSubSequence<AFFGameSequence_ChooseInList>(ChooseListTemplate);
		ChoiceList->SetClassList(Discard->GetCardListAsActor());
	}
}

void AFFGameSequence_VisitDiscard::End()
{
	if (IsServer())
	{
		StopSubSequence(ChoiceList);
	}

	Super::End();
}

void AFFGameSequence_VisitDiscard::OnValidate()
{
	Super::OnValidate();

	if (IsServer())
	{
		StopSubSequence(ChoiceList);
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_VisitDiscard::OnCancel()
{
	Super::OnCancel();

	if (IsServer())
	{
		StopSubSequence(ChoiceList);
		ServerStopCurrentSequence();
	}
}
