// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "FFUtils.generated.h"


const class UFFGameTuning* GetDefaultGameTuning();
const class UFFUITuning* GetDefaultUITuning();

template<typename E>
FString EnumValueAsString(E EnumValue, const TCHAR* EnumName)
{
	static const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, EnumName, true);
	if (!EnumPtr)
		return FString("Enum Not Found");
	return EnumPtr->GetEnumName((int32)EnumValue);
}

#define EnumToString(type, val) EnumValueAsString<type>(val, TEXT(#type))

USTRUCT(BlueprintType)
struct FFFOption
{
	GENERATED_USTRUCT_BODY();

	FFFOption() : Option(""), bEnable(true) {}
	FFFOption(const FString& _Option, bool _bEnable) : Option(_Option), bEnable(_bEnable) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Option;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnable;
};
