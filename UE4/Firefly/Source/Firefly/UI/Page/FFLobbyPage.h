// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "FFLobbyPage.generated.h"

/**
 * 
 */
UCLASS(Category=Firefly)
class UFFLobbyPage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddPlayer(const FString& PlayerName);

	UFUNCTION(BlueprintImplementableEvent, Category = Firefly)
	void BPAddPlayer(const FString& PlayerName);

	UFUNCTION(BlueprintCallable, Category = Firefly)
	void OnButton_LaunchGame();

	UFUNCTION(BlueprintCallable, Category = Firefly)
	void OnButton_Options();
};
