// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFPathFinder.h"
#include "Board/FFSector.h"

FFFPathNode::FFFPathNode()
: Sector(nullptr), Previous(nullptr), DirectCost(MAX_FLT), PathCost(0)
{
}

FFFPathNode::FFFPathNode(AFFSector* _Sector)
: Sector(_Sector), Previous(nullptr), DirectCost(0.f)
{
	check(Sector);

	PathCost = 0.f;
	PathStep = 0;
}

FFFPathNode::FFFPathNode(AFFSector* _Sector, const FFFPathNode& _Previous)
: Sector(_Sector), Previous(_Previous.Sector), DirectCost(0.f)
{
	check(Sector);

	PathCost = (_Previous.Sector != nullptr ? _Previous.PathCost + (_Previous.Sector->GetCenter() - _Sector->GetCenter()).Size() : 0.f);
	PathStep = _Previous.PathStep + 1;
}

FFFPathNode::FFFPathNode(AFFSector* _Sector, AFFSector* _End, const FFFPathNode& _Previous)
: Sector(_Sector), Previous(_Previous.Sector), DirectCost(0.f)
{
	check(Sector);
	check(_End);

	DirectCost = (_End->GetCenter() - _Sector->GetCenter()).Size();
	PathCost = (_Previous.Sector != nullptr ? _Previous.PathCost + (_Previous.Sector->GetCenter() - _Sector->GetCenter()).Size() : 0.f);
	PathStep = _Previous.PathStep + 1;
}

float FFFPathNode::GetTotalCost() const
{
	return PathCost + DirectCost;
}

FFFPath::FFFPath()
{
}

FFFPath::FFFPath(const FFFPath& Src)
{
	Path = Src.Path;
}


FFFPath::FFFPath(AFFSector* Sector)
{
	Path.Add(Sector);
}

FFFPath::FFFPath(const FFFPathNode& Node)
{
	Path.Add(Node);
}

FFFPath::FFFPath(const FFFPath& Src, AFFSector* Sector)
{
	Path = Src.Path;
	AFFSector* OldLast = GetLast();
	Path.Add(Sector);
	Path[Path.Num() - 1].Previous = OldLast;
}

FFFPath::FFFPath(const FFFPath& Src, const FFFPathNode& Node)
{
	Path = Src.Path;
	Path.Add(Node);
}


bool FFFPath::Contains(AFFSector* Sector) const
{
	return Path.ContainsByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Sector); });
}

const FFFPathNode* FFFPath::GetNode(AFFSector* Sector) const
{
	return Path.FindByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Sector); });
}

void FFFPath::Empty()
{
	Path.Empty();
}

bool FFFPath::IsEmpty() const
{
	return (Path.Num() == 0);
}

int32 FFFPath::GetLength() const
{
	return FMath::Max(0, Path.Num() - 1);
}

int32 FFFPath::GetCost() const
{
	return (Path.Num() > 0 ? Path[Path.Num() - 1].GetTotalCost() : 0.f);
}

AFFSector* FFFPath::GetLast() const
{
	return (Path.Num() > 0 ? Path[Path.Num() - 1].Sector : nullptr);
}

UFFPathFinder::UFFPathFinder()
{
}

void UFFPathFinder::FindPath(AFFSector* Start, AFFSector* End, FFFPath& Path)
{
	TArray<FFFPathNode> OpenList;
	TArray<FFFPathNode> CloseList;

	FFFPathNode Previous;

	OpenList.Add(FFFPathNode(Start, End, Previous));

	while (OpenList.Num() > 0)
	{
		OpenList.Sort([](const FFFPathNode& Lhs, const FFFPathNode& Rhs) {
			return Lhs.GetTotalCost() < Rhs.GetTotalCost();
		});

		FFFPathNode Closest = OpenList[0];
		OpenList.RemoveAt(0, 1);

		CloseList.Add(Closest);

		if (Closest.Sector == End)
		{
			Path.Path.Empty();
			FFFPathNode& Last = Closest;
			while (Last.Sector != nullptr)
			{
				Path.Path.Add(Last);
				FFFPathNode* Found = CloseList.FindByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Last.Previous); });
				if (Found == nullptr)
					break;

				Last = *Found;
			}
			break;
		}
		else
		{
			Previous = Closest;
			for (AFFSector* Neigh : Closest.Sector->GetLinks())
			{
				if (OpenList.ContainsByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Neigh); }) == false && CloseList.ContainsByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Neigh); }) == false)
					OpenList.Add(FFFPathNode(Neigh, End, Previous));
			}
		}
	}
}

void UFFPathFinder::GetSectorsAtDist(AFFSector* Start, int Dist, FFFPath& Zone)
{
	TArray<FFFPathNode> OpenList;
	TArray<FFFPathNode> CloseList;

	OpenList.Add(FFFPathNode(Start));

	while (OpenList.Num() > 0)
	{
		FFFPathNode Node = OpenList[0];
		OpenList.RemoveAt(0, 1);

		if (Node.PathStep <= Dist)
		{
			CloseList.Add(Node);

			for (AFFSector* Neigh : Node.Sector->GetLinks())
			{
				if (OpenList.ContainsByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Neigh); }) == false && CloseList.ContainsByPredicate([&](const FFFPathNode& elem) { return (elem.Sector == Neigh); }) == false)
					OpenList.Add(FFFPathNode(Neigh, Node));
			}
		}
	}

	Zone.Path = CloseList;
}

void UFFPathFinder::FindAllPath(const FFFPath& ZoneStart, AFFSector* End, int DistMax, FFFPath& ZoneEnd)
{
	GetSectorsAtDist(End, DistMax, ZoneEnd);

	for (FFFPathNode& Node : ZoneEnd.Path)
	{
		const FFFPathNode* NodeStart = ZoneStart.GetNode(Node.Sector);
		if (NodeStart == nullptr)
			Node.PathStep += DistMax;
		else
			Node.PathStep += NodeStart->PathStep;
	}

	ZoneEnd.Path.RemoveAll([&](const FFFPathNode& elem) { return (elem.PathStep > DistMax); });
}

void UFFPathFinder::FindAllPath(AFFSector* Start, AFFSector* End, int DistMax, FFFPath& outPaths)
{
	FFFPath ZoneStart;
	GetSectorsAtDist(Start, DistMax, ZoneStart);

	FindAllPath(ZoneStart, End, DistMax, outPaths);
}

