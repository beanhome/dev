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

	PathCost = 0;
}

FFFPathNode::FFFPathNode(AFFSector* _Sector, const FFFPathNode& _Previous)
: Sector(_Sector), Previous(_Previous.Sector), DirectCost(0.f)
{
	check(Sector);

	PathCost = _Previous.PathCost + 1;
}

FFFPathNode::FFFPathNode(AFFSector* _Sector, AFFSector* _End, const FFFPathNode& _Previous)
: Sector(_Sector), Previous(_Previous.Sector), DirectCost(0.f)
{
	check(Sector);
	check(_End);

	DirectCost = (_End->GetCenter() - _Sector->GetCenter()).Size();

	PathCost = _Previous.PathCost + 1;
}

float FFFPathNode::GetTotalCost() const
{
	return (float)PathCost + DirectCost;
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

		if (Node.PathCost <= Dist)
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
