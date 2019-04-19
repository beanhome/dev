// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWHud.h"
#include "GSGameState.h"
#include "GSSequence_Main.h"
#include "Game/SWPlayerController.h"

void ASWHud::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas == nullptr || !bShowHUD)
		return;

	float x = 10.f;
	float y = 80.f;

	AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
	if (GameState != nullptr && GameState->Main != nullptr)
		GameState->Main->DrawDebug(Canvas, x, y);

	AGSPlayerController* Player = Cast<AGSPlayerController>(GetOwningPlayerController());
	if (Player)
		Player->DrawDebug(Canvas, x, y);
}