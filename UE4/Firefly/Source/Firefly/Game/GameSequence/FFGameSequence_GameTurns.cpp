// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_GameTurns.h"
#include "FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"
#include "Board/FFSector.h"
#include "Cards/FFDeck.h"
#include "Cards/FFDiscardPile.h"
#include "FFGameSequence_SubGame.h"
#include "FFGameSequence_MultiChooseInList.h"

AFFGameSequence_GameTurns::AFFGameSequence_GameTurns()
{
}

void AFFGameSequence_GameTurns::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_GameTurns, SubSequences);
}

void AFFGameSequence_GameTurns::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

bool AFFGameSequence_GameTurns::IsCameraFree() const
{
	for (AFFGameSequence* Sequence : SubSequences)
	{
		check(Sequence != nullptr);

		if (Sequence->IsCameraFree() == false)
			return false;
	}

	return true;
}

bool AFFGameSequence_GameTurns::IsTurnOf(int32 id) const
{
	return (CurrentPlayerId == id);
}

bool AFFGameSequence_GameTurns::IsMyTurn() const
{
	return (IsClient() && CurrentPlayerId == GetMyPlayerId());
}

const FFFPlayer& AFFGameSequence_GameTurns::GetPlayingPlayer() const
{
	return GetGame()->GetPlayer(CurrentPlayerId);
}

const FFFPlayer& AFFGameSequence_GameTurns::GetMyPlayer() const
{
	return GetGame()->GetPlayer(GetMyPlayerId());
}

void AFFGameSequence_GameTurns::ServerStart()
{
	Super::ServerStart();

	AFFGameSequence_Game* GameOwner = GetOwner<AFFGameSequence_Game>();
	CurrentPlayerId = GameOwner->GetPlayersOrder()[0];

	StartPlayerTurn(CurrentPlayerId);
}


void AFFGameSequence_GameTurns::Start()
{
	Super::Start();
}

void AFFGameSequence_GameTurns::End()
{
	Super::End();
}

void AFFGameSequence_GameTurns::StartPlayerTurn_Implementation(int32 id)
{
	if (IsClient())
	{
		SEQLOG();

		AFFGameSequence_Game* GameOwner = GetOwner<AFFGameSequence_Game>();
		CurrentPlayerId = id;

		if (CurrentPlayerId == GetMyPlayerId())
		{
			if (GetHud())
				GetHud()->Title = TEXT("It is your turn !");
		}
		else
		{
			if (GetHud())
				GetHud()->Title = TEXT("Other Player Turn");
		}
	}
}

void AFFGameSequence_GameTurns::ConsumeAction(class AFFGameSequence_SubTurn* Action)
{
	check(IsServer());

	CurrentActionDones.Add(Action);

	if (CurrentActionDones.Num() == 2)
	{
		FinishPlayerGameTurns(CurrentPlayerId);

		AFFGameSequence_Game* GameOwner = GetOwner<AFFGameSequence_Game>();
		CurrentPlayerId = (CurrentPlayerId + 1) % GameOwner->GetPlayersOrder().Num();
		StartPlayerTurn(CurrentPlayerId);
		CurrentActionDones.Empty();
	}
}

void AFFGameSequence_GameTurns::FinishPlayerGameTurns_Implementation(int32 id)
{
	if (GetHud())
		GetHud()->Title = TEXT("");
}


bool AFFGameSequence_GameTurns::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	// Deck or Discard Clicked
	// -> Sequence Choose in List

	AFFDiscardPile* DiscardPile = Cast<AFFDiscardPile>(Actor);
	AFFDeck* Deck = Cast<AFFDeck>(Actor);

	if (DiscardPile == nullptr && Deck != nullptr)
		DiscardPile = Deck->GetDiscardPile();

	// TEST
	if (IsServer() && Deck != nullptr)
	{
		AFFGameSequence_MultiChooseInList* ChooseSeq = StartSubSequence<AFFGameSequence_MultiChooseInList>(DiscardPile->MultiChooseInListTemplate);
		ChooseSeq->SetCardList(Deck->GetCardList());
		return true;
	}

	if (IsServer() && DiscardPile != nullptr)
	{
		AFFGameSequence_MultiChooseInList* ChooseSeq = StartSubSequence<AFFGameSequence_MultiChooseInList>(DiscardPile->MultiChooseInListTemplate);
		ChooseSeq->SetCardList(DiscardPile->GetCardList());
	}


	// Own Ship Sector
	// -> Sequence ChooseInList
	// -> Sequence Flying
	if (Cast<AFFSector>(Actor) != nullptr)
	{
		if (IsUnderCamera(BoardCameraName) == false)
			return false;

		AFFSector* ClickedSector = Cast<AFFSector>(Actor);

		if (IsServer() && PlayerId == CurrentPlayerId)
		{
			const FFFPlayer& Player = GetGame()->GetPlayer(PlayerId);
			const AFFSector* ShipSector = Player.Ship->GetCurrentSector();

			if (ClickedSector == ShipSector)
			{
				StartSubSequence<AFFGameSequence_Fly>(GetDefaultGameTuning()->GameSequence_Fly);
			}
		}
	}

	return false;
}

bool AFFGameSequence_GameTurns::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	if (GetMyPlayerId() == PlayerId)
	{
		const FFFPlayer& Player = GetMyPlayer();
		AFFSector* ShipSector = Player.Ship->GetCurrentSector();

		if (Actor == ShipSector)
		{
			ShipSector->HighLight(true);
		}
	}

	return false;
}

bool AFFGameSequence_GameTurns::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	if (GetMyPlayerId() == PlayerId)
	{
		const FFFPlayer& Player = GetMyPlayer();
		AFFSector* ShipSector = Player.Ship->GetCurrentSector();

		if (Actor == ShipSector)
		{
			ShipSector->HighLight(false);
		}
	}

	return false;
}


void AFFGameSequence_GameTurns::ServerReceiveResponse(int32 res)
{
	SEQLOG();

	/*
	GetOwner<AFFGameSequence_Game>()->PlayerGameTurns(PlayersOrder[CurrentPlayerIndex], res);

	FinishPlayerGameTurns(PlayersOrder[CurrentPlayerIndex]);
		
	CurrentPlayerIndex--;

	if (CurrentPlayerIndex >= 0)
		StartPlayerGameTurns(PlayersOrder[CurrentPlayerIndex]);
	else
		ServerStopCurrentSequence();
	*/
}

void AFFGameSequence_GameTurns::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColorList::Grey);

	y += Canvas->DrawText(Font, FString::Printf(TEXT("Current Player Turn %d"), CurrentPlayerId), x, y);
}


