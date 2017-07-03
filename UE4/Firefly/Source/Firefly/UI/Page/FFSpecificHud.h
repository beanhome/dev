// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "FFSpecificHud.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpecificHudButtonDelegate);

/**
 * 
 */
UCLASS(Category=Firefly)
class UFFSpecificHud : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Firefly)
	void OnButton_Validate();

	UFUNCTION(BlueprintCallable, Category = Firefly)
	void OnButton_Cancel();

public:
	UPROPERTY()
	FSpecificHudButtonDelegate ValidateDelegate;

	UPROPERTY()
	FSpecificHudButtonDelegate CancelDelegate;
};
