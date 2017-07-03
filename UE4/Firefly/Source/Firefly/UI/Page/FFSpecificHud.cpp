// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "FFSpecificHud.h"

#include "Game/FireflyPlayerController.h"


void UFFSpecificHud::OnButton_Validate()
{
	ValidateDelegate.Broadcast();
}

void UFFSpecificHud::OnButton_Cancel()
{
	CancelDelegate.Broadcast();
}



