// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSequence.h"
#include "GSGameModeBase.h"
#include "GSPlayerController.h"
#include "GSGameState.h"
#include "TimerManager.h"

AGSGameModeBase::AGSGameModeBase()
: PlayerCount(0)
, HostPlayer(nullptr)
{
	DefaultPawnClass = NULL;
	PlayerControllerClass = AGSPlayerController::StaticClass();
	GameStateClass = AGSGameState::StaticClass();
}


void AGSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGSGameModeBase::StartGame, 0.5f);
}


void AGSGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(GameSequence, Log, TEXT("----------------  AGSGameModeBase::PostLogin %s"), *NewPlayer->GetName());

	AGSPlayerController* Player = Cast<AGSPlayerController>(NewPlayer);
	Player->SetId(PlayerCount);

	if (PlayerCount == 0)
		HostPlayer = Player;

	PlayerCount++;
}

void AGSGameModeBase::StartGame()
{
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AGSPlayerController* Controller = Cast<AGSPlayerController>(*It);

		if (Controller != nullptr)
		{
			UE_LOG(GameSequence, Log, TEXT("  **********   Server AFireflyGameMode::StartGame Controller %s"), *Controller->GetName());
			Controller->StartGame();
		}
	}

	GetWorld()->GetGameState<AGSGameState>()->StartGame(MainGameSequenceClass);
}
