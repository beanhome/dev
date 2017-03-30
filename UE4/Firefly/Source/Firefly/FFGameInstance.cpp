// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameInstance.h"

void UFFGameInstance::Init()
{
	Super::Init();
}

bool UFFGameInstance::JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults)
{
	return Super::JoinSession(LocalPlayer, SessionIndexInSearchResults);
}

bool UFFGameInstance::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	return Super::JoinSession(LocalPlayer, SearchResult);
}

