// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "FFQuestionPopup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestionPopupDelegate, int32, id);

/**
 * 
 */
UCLASS(Category=Firefly)
class UFFQuestionPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTitle(const FString& title);
	void SetDesc(const FString& desc);
	void SetOptions(const TArray<FFFOption>& options);
	void AddOption(const FString& option);

	UFUNCTION(BlueprintImplementableEvent, Category = Firefly)
	void BPSetOptions(const TArray<FFFOption>& options);

	UFUNCTION(BlueprintCallable, Category = Firefly)
	void OnButton_Select(int32 id);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFFOption> Options;

	UPROPERTY()
	FQuestionPopupDelegate SelectAnswerDelegate;
};
