// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FireflyGameMode.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_ChooseLeaderAndShip.h"
#include "FFGameSequence_PlaceShip.h"
#include "FFGameSequence_GameTurns.h"
#include "Game/FireflyPlayerController.h"
#include "Game/FFUITuning.h"
#include "Cards/Cards/FFLeaderCard.h"
#include "Cards/FFDeck.h"
#include "Board/FFShipBoard.h"
#include "Board/FFShipBoardPlace.h"
#include "UI/Page/FFGameHud.h"

AFFGameSequence_Game::AFFGameSequence_Game()
{
}

bool AFFGameSequence_Game::IsSupportedForNetworking() const
{
	return true;
}

void AFFGameSequence_Game::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_Game, Players);
}

UFFGameHud* AFFGameSequence_Game::GetGameHud()
{
	return GameHUD;
}

const TArray<int32>& AFFGameSequence_Game::GetPlayersOrder() const
{
	return PlayersOrder;
}


bool AFFGameSequence_Game::IsCameraFree() const
{
	return Super::IsCameraFree();
}

const FFFPlayer& AFFGameSequence_Game::GetPlayer(int32 Id) const
{
	check(Id < Players.Num());

	return Players[Id];
}

void AFFGameSequence_Game::ServerInit(AFFGameSequence* OwnerSequence)
{
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AFireflyPlayerController* Controller = Cast<AFireflyPlayerController>(*It);
		if (Players.Num() <= Controller->GetId())
			Players.SetNum(Controller->GetId() + 1);
		Players[Controller->GetId()] = FFFPlayer();
	}

	Super::ServerInit(OwnerSequence);
}

void AFFGameSequence_Game::ReceiveMouseEnterActor_Implementation(int32 PlayerId, class AFFActor* Actor)
{
	PropagateMouseEnterActor(PlayerId, Actor);
}

void AFFGameSequence_Game::ReceiveMouseLeaveActor_Implementation(int32 PlayerId, class AFFActor* Actor)
{
	PropagateMouseLeaveActor(PlayerId, Actor);
}

void AFFGameSequence_Game::ReceiveMouseClickActor_Implementation(int32 PlayerId, class AFFActor* Actor)
{
	PropagateMouseClickActor(PlayerId, Actor);
}

void AFFGameSequence_Game::Init(AFFGameSequence* OwnerSequence)
{
	for (TActorIterator<AFFShipBoardPlace> It(GetWorld()); It; ++It)
	{
		AFFShipBoardPlace* Place = *It;
		Place->SetActorHiddenInGame(true);
	}

	Super::Init(OwnerSequence);
}


void AFFGameSequence_Game::Start()
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	Super::Start();

	const UFFUITuning* UITuning = GetDefaultUITuning();
	if (PlayerController && UITuning->GameHUDClass.GetDefaultObject())
	{
		GameHUD = CreateWidget<UFFGameHud>(PlayerController, UITuning->GameHUDClass);
		GameHUD->AddToViewport();

		GameHUD->Id = PlayerController->GetId();
		GameHUD->Title = GetClass()->GetName();
	}

	if (IsServer())
	{
		//NavigationAllianceDeck->Init(GetDefaultGameTuning()->NavigationAllianceDeck);

		ShufflePlayerOrder();

		AFFGameSequence* SubSequence = StartSubSequence<AFFGameSequence_ChooseLeaderAndShip>();
		SubSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Game::ChooseLeaderAndShipFinish);
	}
}

void AFFGameSequence_Game::ChooseLeaderAndShipFinish(AFFGameSequence* Seq)
{
	SEQLOG();

	StopSubSequence(Seq);

	AFFGameSequence* SubSequence = StartSubSequence<AFFGameSequence_PlaceShip>(GetDefaultGameTuning()->GameSequence_PlaceShip);
	SubSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Game::PlaceShipFinish);
}

void AFFGameSequence_Game::PlaceShipFinish(AFFGameSequence* Seq)
{
	SEQLOG();

	StopSubSequence(Seq);

	AFFGameSequence* SubSequence = StartSubSequence<AFFGameSequence_GameTurns>();
	SubSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Game::GameOver);
}

void AFFGameSequence_Game::GameOver(AFFGameSequence* Seq)
{
}

void AFFGameSequence_Game::PlayerChooseLeader(int32 PlayerId, TSubclassOf<class AFFActor>& LeaderCard)
{
	ensure(IsServer());

	AFFLeaderCard* Leader = GetWorld()->SpawnActor<AFFLeaderCard>(LeaderCard);
	Players[PlayerId].Leader = Leader;
	Leader->SetActorHiddenInGame(true);
}

void AFFGameSequence_Game::PlayerChooseShip(int32 PlayerId, TSubclassOf<class AFFActor>& ShipCard)
{
	ensure(IsServer());

	AFFShipBoard* ShipBoard = GetWorld()->SpawnActor<AFFShipBoard>(ShipCard);
	AFFEngineCard* Engine = GetWorld()->SpawnActor<AFFEngineCard>(ShipBoard->DefaultEngine);
	Players[PlayerId].ShipBoard = ShipBoard;
	Players[PlayerId].Engine = Engine;
	ShipBoard->ClientInitialize(PlayerId, Players[PlayerId].Leader, Engine);
}

void AFFGameSequence_Game::PlayerPlaceShip(int32 PlayerId, int32 SectorId)
{
	AFFShip* Ship = GetWorld()->SpawnActor<AFFShip>(Players[PlayerId].ShipBoard->DefaultShip);
	Players[PlayerId].Ship = Ship;
	Ship->SetSector(SectorId);
	Ship->ClientInitialize(PlayerId);
}

void AFFGameSequence_Game::End()
{
	if (GameHUD != nullptr)
	{
		GameHUD->RemoveFromParent();
		GameHUD = nullptr;
	}

	Super::End();
}

void AFFGameSequence_Game::ShufflePlayerOrder()
{
	AFireflyGameMode* const GameMode = GetWorld()->GetAuthGameMode<AFireflyGameMode>();
	check(GameMode != nullptr);

	int32 Size = GameMode->GetPlayerCount();
	PlayersOrder.SetNum(Size);
	for (int32 i = 0; i < Size; ++i)
		PlayersOrder[i] = Size-1-i;
	for (int32 i = 0; i < Size; ++i)
		PlayersOrder.Swap(i, FMath::RandRange(0, Size-1));
}
