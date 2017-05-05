// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "FFHud.h"
#include "FFGameState.h"

void AFFHud::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas == nullptr || !bShowHUD)
		return;

	float x = 10.f;
	float y = 50.f;

	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
	{
		GameState->Game->DrawDebug(Canvas, x, y);
	}

	AFireflyPlayerController* Player = Cast<AFireflyPlayerController>(GetOwningPlayerController());
	if (Player)
		Player->DrawDebug(Canvas, x, y);

}