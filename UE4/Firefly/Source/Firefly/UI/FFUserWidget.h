// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "FFUserWidget.generated.h"

/**
 * 
 */
UCLASS(Category=Firefly)
class UFFUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	int32 GetIntProperty(const FString& PropName) const;
	void SetIntProperty(const FString& PropName, int32 val);

	FString GetStringProperty(const FString& PropName) const;
	void SetStringProperty(const FString& PropName, const FString& val);

public:
};
