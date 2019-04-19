// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSequence.h"
#include "GSSequence_OneGameTurn_Base.h"

AGSSequence_OneGameTurn_Base::AGSSequence_OneGameTurn_Base()
: PlayerCount(1)
{
}

bool AGSSequence_OneGameTurn_Base::IsTurnOf(int32 id) const
{
	return (CurrentPlayerId == id);
}

bool AGSSequence_OneGameTurn_Base::IsMyTurn() const
{
	return (IsClient() && CurrentPlayerId == GetMyPlayerId());
}

void AGSSequence_OneGameTurn_Base::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);

	if (InitParameter != nullptr)
	{
		PlayerCount = ((AGSSequence_OneGameTurn_Base::FInit*)InitParameter)->PlayerCount;
		PlayersOrder = ((AGSSequence_OneGameTurn_Base::FInit*)InitParameter)->PlayersOrder;
		OnePlayerTurnSequence = ((AGSSequence_OneGameTurn_Base::FInit*)InitParameter)->OnePlayerTurnSequence;
	}

	if (PlayersOrder.Num() > 0)
	{
		PlayerCount = PlayersOrder.Num();
	}
	else
	{
		PlayersOrder.SetNum(PlayerCount);
		for (int32 i = 0; i < PlayerCount; ++i)
			PlayersOrder[i] = i;
	}
}

void AGSSequence_OneGameTurn_Base::Start()
{
	Super::Start();

	if (IsServer())
	{
		StartPlayerTurn(0);
	}
}

void AGSSequence_OneGameTurn_Base::End()
{
	Super::End();
}

void AGSSequence_OneGameTurn_Base::StartPlayerTurn(int32 index)
{
	check(IsServer());

	CurrentPlayerIndex = index;
	CurrentPlayerId = (CurrentPlayerIndex < PlayersOrder.Num() ? PlayersOrder[CurrentPlayerIndex] : CurrentPlayerIndex);

	OnStartPlayerTurn(CurrentPlayerId);

	if (OnePlayerTurnSequence.GetDefaultObject() != nullptr)
		StartSubSequence(OnePlayerTurnSequence, this, &AGSSequence_OneGameTurn_Base::OnPlayerTurnFinish);
}

void AGSSequence_OneGameTurn_Base::OnPlayerTurnFinish(AGSSequence* Seq)
{
	StopPlayerTurn();
}

void AGSSequence_OneGameTurn_Base::StopPlayerTurn()
{
	check(IsServer());

	OnStopPlayerTurn();

	int32 NextPlayerIndex = CurrentPlayerIndex + 1;
	if (NextPlayerIndex >= PlayerCount)
	{
		ServerStopCurrentSequence();
	}
	else
	{
		StartPlayerTurn(NextPlayerIndex);
	}
}

void AGSSequence_OneGameTurn_Base::OnStartPlayerTurn_Implementation(int32 id)
{
	CurrentPlayerId = id; // symchro client

	BeginPlayerTurn();
}

void AGSSequence_OneGameTurn_Base::OnStopPlayerTurn_Implementation()
{
	EndPlayerTurn();
}

void AGSSequence_OneGameTurn_Base::BeginPlayerTurn()
{
	// to implement in child class
}

void AGSSequence_OneGameTurn_Base::EndPlayerTurn()
{
	// to implement in child class
}


void AGSSequence_OneGameTurn_Base::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColorList::White);

	FString str = "(";
	if (PlayersOrder.Num() > 0)
	{
		for (int32 i : PlayersOrder)
			str += FString::Printf(TEXT("%d, "), i);
		str[str.Len() - 2] = ')';
	}
	else
	{
		str += ")";
	}

	y += Canvas->DrawText(Font, FString::Printf(TEXT("Player %d %s"), CurrentPlayerId, *str), x, y);
}
