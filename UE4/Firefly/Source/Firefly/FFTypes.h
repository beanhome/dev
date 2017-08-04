// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "FFTypes.generated.h"

USTRUCT()
struct FFFPlayer
{
	GENERATED_BODY()

	UPROPERTY()
	class AFFLeaderCard* Leader;

	UPROPERTY()
	class AFFShipBoard* ShipBoard;

	UPROPERTY()
	class AFFEngineCard* Engine;

	UPROPERTY()
	class AFFShip* Ship;

	UPROPERTY()
	int32 Credits;
};

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

	/*
	bool IsValid(const FFFPlayer& Player) const
	{
		for (const TSubclassOf<class AFFGameSequence_Effect>& Effect : Sequences)
		{
			if (Effect.GetDefaultObject() && Effect.GetDefaultObject()->IsValid(Player) == false)
				return false;
		}

		return true;
	}
	*/
};

USTRUCT(BlueprintType)
struct FFFPurchaseStuff
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class AFFStuff> Stuff;

	UPROPERTY(BlueprintReadWrite)
	int32 Count;

	UPROPERTY(BlueprintReadWrite)
	int32 Price;
};
