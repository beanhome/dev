// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Engine/GameInstance.h"
#include "FFGameInstance.generated.h"

UCLASS(ClassGroup = "Firefly")
class UFFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults) override;
	virtual bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult) override;
private:
};



