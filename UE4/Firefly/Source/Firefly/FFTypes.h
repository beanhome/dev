// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "FFTypes.generated.h"

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

USTRUCT()
struct FFFGSCardChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFFGameSequence_Effect> > Sequences;

	//UPROPERTY(EditAnywhere)
	//TArray<TSubclassOf<AFFCondition> > Conditions;

	UPROPERTY()
	class USceneComponent* Selector;
};
