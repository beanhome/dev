// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFPathFinder.generated.h"

class AFFPlayerPawn;
class AFFSector;
class AFFCard;
class AFFEngineCard;

USTRUCT()
struct FFFPathNode
{
	GENERATED_BODY()

	FFFPathNode();
	FFFPathNode(AFFSector* _Sector);
	FFFPathNode(AFFSector* _Sector, const FFFPathNode& _Previous);
	FFFPathNode(AFFSector* _Sector, AFFSector* _End, const FFFPathNode& _Previous);
	float GetTotalCost() const;

	UPROPERTY()
	AFFSector* Sector;

	UPROPERTY()
	AFFSector* Previous;

	float DirectCost;
	int PathCost;
};

USTRUCT()
struct FFFPath
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FFFPathNode> Path;
};

UCLASS(minimalapi)
class UFFPathFinder : public UObject
{
	GENERATED_BODY()

public:
	UFFPathFinder();

	void FindPath(AFFSector* Start, AFFSector* End, FFFPath& Path);
	void GetSectorsAtDist(AFFSector* Start, int Dist, FFFPath& Zone);

private:

};



