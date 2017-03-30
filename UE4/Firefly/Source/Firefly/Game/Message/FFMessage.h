// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFMessage.generated.h"

UCLASS(minimalapi)
class UFFMessage : public UObject
{
	GENERATED_BODY()

public:
	UFFMessage();

private:
};

UCLASS(minimalapi)
class UFFMessage_Test : public UFFMessage
{
	GENERATED_BODY()

public:
	UFFMessage_Test();
	UFFMessage_Test(int32 val);

public:
	UPROPERTY()
	int32 popolop;
};



