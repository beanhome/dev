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
	float PathCost;
	int32 PathStep;
};

USTRUCT()
struct FFFPath
{
	GENERATED_BODY()

	FFFPath();
	FFFPath(const FFFPath& Src);
	FFFPath(AFFSector* Sector);
	FFFPath(const FFFPathNode& Node);
	FFFPath(const FFFPath& Src, AFFSector* Sector);
	FFFPath(const FFFPath& Src, const FFFPathNode& Node);

	bool Contains(AFFSector* Sector) const;
	const FFFPathNode* GetNode(AFFSector* Sector) const;
	int32 GetLength() const;
	int32 GetCost() const;
	AFFSector* GetLast() const;

	void Empty();
	bool IsEmpty() const;

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
	void FindAllPath(AFFSector* Start, AFFSector* End, int DistMax, FFFPath& outPaths);
	void FindAllPath(const FFFPath& ZoneStart, AFFSector* End, int DistMax, FFFPath& outPaths);

private:

};



