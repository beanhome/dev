// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "SWGameHud.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSWGameHud_EndTurnDelegate);

/**
 * 
 */
UCLASS()
class SHADOWWAR_API USWGameHud : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetClientId(int32 id);
	void SetPlayerId(int32 id);
	void SetTitle(const FString& title);

	UFUNCTION(BlueprintImplementableEvent)
	void SetEndTurnButton(bool bVisible, const FString& Text = "");

	UFUNCTION(BlueprintCallable)
	void OnClickEndTurn();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(BlueprintAssignable)
	FSWGameHud_EndTurnDelegate EndTurnDelegate;
};
