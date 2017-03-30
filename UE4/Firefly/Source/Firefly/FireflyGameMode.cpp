// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FireflyGameMode.h"
#include "Game/FFPlayerInfo.h"
#include "Game/FFPlayerPawn.h"
#include "Game/FFGameTuning.h"
#include "Game/FFUITuning.h"
#include "Game/FFGameTurn.h"
#include "Game/GameSequence/FFGameSequence.h"
#include "Game/GameSequence/FFGameSequence_Game.h"
#include "Game/FireflyPlayerController.h"
#include "FFGameState.h"
#include "Game/Message/FFMessage.h"

AFireflyGameMode::AFireflyGameMode()
: GamePhase(EFFGamePhase::Lobby)
, PlayerCount(1)
, TurnNumber(0)
, PlayerActive(0)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = AFireflyPlayerController::StaticClass();
	GameStateClass = AFFGameState::StaticClass();

	GetDefaultGameTuning();
	GetDefaultUITuning();
}

void AFireflyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* InWorld = GetWorld();
	if (InWorld == nullptr || InWorld->IsPendingKill())
		return;
}

void AFireflyGameMode::PreLogin(const FString& Options, const FString& Address, const TSharedPtr<const FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AFireflyGameMode::Login(class UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const TSharedPtr<const FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AFireflyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(Firefly, Log, TEXT("----------------  AFireflyGameMode::PostLogin %s"), *NewPlayer->GetName());

	UFFPlayerInfo* PlayerInfo = NewObject<UFFPlayerInfo>(GetWorld());
	PlayerInfo->Init(NewPlayer, *FString::Printf(TEXT("A%1d"), Players.Num() + 1));
	Players.Add(PlayerInfo);

	if (GamePhase == EFFGamePhase::Lobby)
	{
		AFireflyPlayerController* Player = Cast<AFireflyPlayerController>(NewPlayer);

		if (HostPlayer == nullptr)
		{
			HostPlayer = Player;
			HostPlayer->NotifySetHost();
		}
		else
		{
			Player->NotifySetGuest();
			HostPlayer->NotifyNewPlayer(NewPlayer);
		}
	}
}

const TArray<UFFPlayerInfo*>& AFireflyGameMode::GetPlayers() const
{
	return Players;
}

TArray<UFFPlayerInfo*>& AFireflyGameMode::GetPlayers()
{
	return Players;
}

const UFFPlayerInfo* AFireflyGameMode::GetPlayerInfo(int32 id) const
{
	return *Players.FindByPredicate([&](const UFFPlayerInfo* elem) { return (elem->GetId() == id); });
}

UFFPlayerInfo* AFireflyGameMode::GetPlayerInfo(int32 id)
{
	return *Players.FindByPredicate([&](const UFFPlayerInfo* elem) { return (elem->GetId() == id); });
}

const UFFPlayerInfo* AFireflyGameMode::GetPlayerInfo(AFireflyPlayerController* PC) const
{
	return *Players.FindByPredicate([&](const UFFPlayerInfo* elem) { return (elem->GetController() == PC); });
}

UFFPlayerInfo* AFireflyGameMode::GetPlayerInfo(AFireflyPlayerController* PC)
{
	return *Players.FindByPredicate([&](const UFFPlayerInfo* elem) { return (elem->GetController() == PC); });
}


void AFireflyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UFFPlayerInfo* AFireflyGameMode::GetActivePlayer() const
{
	return (Players.Num() > 0 && PlayerActive < Players.Num() ? Players[PlayerActive] : nullptr);
}

void AFireflyGameMode::StartGame()
{
	UE_LOG(Firefly, Log, TEXT("  **********   AFireflyGameMode::StartGame (World %x)"), GetWorld());

	for (int32 i = 0; i < Players.Num(); ++i)
		Players[i]->SetId(i);

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AFireflyPlayerController* Controller = Cast<AFireflyPlayerController>(*It);

		UE_LOG(Firefly, Log, TEXT("  **********   Server AFireflyGameMode::StartGame Controller %s"), *Controller->GetName());

		UFFPlayerInfo* PlayerInfo = GetPlayerInfo(Controller);
		Controller->SetId(PlayerInfo->GetId());
		Controller->StartGame(PlayerInfo->GetId());

		/*
		UFFMessage_Test* Msg = NewObject<UFFMessage_Test>();
		Msg->popolop = 65;
		Controller->Message(Msg);
		*/
	}

	GetWorld()->GetGameState<AFFGameState>()->StartGame();
}

void AFireflyGameMode::StartPlayerTurn()
{
	CurrentTurn = NewObject<AFFGameTurn>(this);
	CurrentTurn->Init(nullptr);
	CurrentTurn->Start();
}

void AFireflyGameMode::EndPlayerTurn()
{
	CurrentTurn = nullptr;

}