// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWGameModeBase.h"
#include "Game/SWGameTuning.h"
#include "Game/SWPlayerController.h"
#include "GSGameState.h"
#include "UI/SWHud.h"

ASWGameModeBase::ASWGameModeBase()
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = ASWPlayerController::StaticClass();
	GameStateClass = AGSGameState::StaticClass();
	HUDClass = ASWHud::StaticClass();

	GetDefaultGameTuning();
	GetDefaultUITuning();

	MainGameSequenceClass = GetDefaultGameTuning()->MainGameSequenceClass;
}


