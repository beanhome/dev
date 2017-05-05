// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FFHud.generated.h"

/**
 * 
 */
UCLASS(Category=Firefly)
class AFFHud : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

public:
};
