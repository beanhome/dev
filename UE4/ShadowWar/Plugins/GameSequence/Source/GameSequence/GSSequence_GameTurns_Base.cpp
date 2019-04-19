// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSequence.h"
#include "GSSequence_GameTurns_Base.h"

AGSSequence_GameTurns_Base::AGSSequence_GameTurns_Base()
: MaximumTurnCount(-1)
{
}

void AGSSequence_GameTurns_Base::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);

	if (InitParameter != nullptr)
	{
		MaximumTurnCount = ((AGSSequence_GameTurns_Base::FInit*)InitParameter)->MaximumTurnCount;
		OneGameTurnSequence = ((AGSSequence_GameTurns_Base::FInit*)InitParameter)->OneGameTurnSequence;
	}
}

void AGSSequence_GameTurns_Base::Start()
{
	Super::Start();

	if (IsServer())
	{
		StartGameTurn(0);
	}
}

void AGSSequence_GameTurns_Base::End()
{
	Super::End();
}

void AGSSequence_GameTurns_Base::StartGameTurn(int32 turn)
{
	check(IsServer());

	CurrentTurn = turn;

	OnStartGameTurn(turn);

	if (OneGameTurnSequence.GetDefaultObject() != nullptr)
		StartSubSequence(OneGameTurnSequence, this, &AGSSequence_GameTurns_Base::OnGameTurnFinish);
}

void AGSSequence_GameTurns_Base::OnGameTurnFinish(AGSSequence* Seq)
{
	StopGameTurn();
}

void AGSSequence_GameTurns_Base::StopGameTurn()
{
	check(IsServer());

	OnStopGameTurn();

	int32 NextTurn = CurrentTurn + 1;

	if (MaximumTurnCount > 0 && NextTurn > MaximumTurnCount)
	{
		ServerStopCurrentSequence();
	}
	else
	{
		StartGameTurn(NextTurn);
	}
}

void AGSSequence_GameTurns_Base::OnStartGameTurn_Implementation(int32 turn)
{
	CurrentTurn = turn; // synchro client

	BeginGameTurn();
}

void AGSSequence_GameTurns_Base::OnStopGameTurn_Implementation()
{
	EndGameTurn();
}

void AGSSequence_GameTurns_Base::BeginGameTurn()
{
	// to implement in child class
}

void AGSSequence_GameTurns_Base::EndGameTurn()
{
	// to implement in child class
}

void AGSSequence_GameTurns_Base::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColor::White);

	if (MaximumTurnCount > 0)
		y += Canvas->DrawText(Font, FString::Printf(TEXT("Turn %d / %d"), CurrentTurn, MaximumTurnCount), x, y);
	else
		y += Canvas->DrawText(Font, FString::Printf(TEXT("Turn %d"), CurrentTurn), x, y);
}
