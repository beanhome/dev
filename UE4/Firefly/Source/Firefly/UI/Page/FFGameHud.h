// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "FFGameHud.generated.h"

/**
 * 
 */
UCLASS(Category=Firefly)
class UFFGameHud : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetId(int32 id);
	void SetTitle(const FString& title);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;
};
