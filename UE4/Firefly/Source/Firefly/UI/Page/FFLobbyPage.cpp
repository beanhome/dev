// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "FFLobbyPage.h"

#include "Game/FireflyPlayerController.h"

void UFFLobbyPage::AddPlayer(const FString& PlayerName)
{
	BPAddPlayer(PlayerName);
}


void UFFLobbyPage::OnButton_LaunchGame()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	AFireflyPlayerController* PlayerController(GameInstance != nullptr ? Cast<AFireflyPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);

	if (PlayerController)
		PlayerController->ServerLaunchGame();
}

void UFFLobbyPage::OnButton_Options()
{

}



