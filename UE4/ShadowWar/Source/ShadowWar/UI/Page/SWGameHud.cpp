// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWGameHud.h"


void USWGameHud::SetClientId(int32 id)
{
	ClientId = id;
}

void USWGameHud::SetPlayerId(int32 id)
{
	PlayerId = id;
}

void USWGameHud::SetTitle(const FString& title)
{
	Title = title;
}

void USWGameHud::OnClickEndTurn()
{
	EndTurnDelegate.Broadcast();
}



