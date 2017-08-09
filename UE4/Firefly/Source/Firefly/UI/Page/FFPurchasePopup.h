// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FFSpecificHud.h"

#include "FFPurchasePopup.generated.h"

/**
 * 
 */
UCLASS(Category=Firefly)
class UFFPurchasePopup : public UFFSpecificHud
{
	GENERATED_BODY()
	
public:
	void SetTitle(const FString& title);
	void SetDesc(const FString& desc);
	void SetPurchaseStuff(const TArray<struct FFFPurchaseStuff>& _Stuffs);

	UFUNCTION(BlueprintImplementableEvent, Category = Firefly)
	void BPSetPurchaseStuff(const TArray<struct FFFPurchaseStuff>& _Stuffs);

	UFUNCTION(BlueprintCallable, Category = Firefly)
	void OnItemChange();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FFFPurchaseStuff> Stuffs;

};
