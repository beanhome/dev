// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "FFPurchasePopup.h"

void UFFPurchasePopup::SetTitle(const FString& title)
{
	Title = title;
}

void UFFPurchasePopup::SetDesc(const FString& desc)
{
	Desc = desc;
}

void UFFPurchasePopup::SetPurchaseStuff(const TArray<struct FFFPurchaseStuff>& _Stuffs)
{
	Stuffs = _Stuffs;

	for (FFFPurchaseStuff& Stuff : Stuffs)
		if (Stuff.Max <= 0)
			Stuff.Max = 99;
			
	BPSetPurchaseStuff(Stuffs);
}

const TArray<struct FFFPurchaseStuff>& UFFPurchasePopup::GetPurchaseStuff() const
{
	return Stuffs;
}

void UFFPurchasePopup::SetCash(int32 iCash)
{
	Cash = iCash;
	BPSetCash(Cash);
}

void UFFPurchasePopup::OnItemChange()
{
	int32 iCost = 0;

	for (FFFPurchaseStuff& Stuff : Stuffs)
	{
		Stuff.Count = FMath::Clamp(Stuff.Count, 0, Stuff.Max);
		iCost += Stuff.Count * Stuff.Price;
	}

	BPSetPurchaseStuff(Stuffs);
	BPSetCash(Cash - iCost);
}

