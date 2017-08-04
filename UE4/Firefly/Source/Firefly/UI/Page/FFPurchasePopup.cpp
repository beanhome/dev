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
	BPSetPurchaseStuff(Stuffs);

}

void UFFPurchasePopup::OnItemChange()
{

}

