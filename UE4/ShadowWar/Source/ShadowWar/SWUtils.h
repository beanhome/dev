// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

//#include "SWUtils.generated.h"

const class USWGameTuning* GetDefaultGameTuning();
const class USWUITuning* GetDefaultUITuning();

template<typename E>
FString EnumValueAsString(E EnumValue, const TCHAR* EnumName)
{
	static const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, EnumName, true);
	if (!EnumPtr)
		return FString("Enum Not Found");
	return EnumPtr->GetEnumName((int32)EnumValue);
}

#define EnumToString(type, val) EnumValueAsString<type>(val, TEXT(#type))
