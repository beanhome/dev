// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Purchase.h"
#include "UI/Page/FFPurchasePopup.h"

AFFGameSequence_Purchase::AFFGameSequence_Purchase()
{
}

void AFFGameSequence_Purchase::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_Purchase::Start()
{
	Super::Start();

	UFFPurchasePopup* PurchasePopup = Cast<UFFPurchasePopup>(SpecificHud);
	
	if (PurchasePopup != nullptr)
	{
		PurchasePopup->SetPurchaseStuff(Stuffs);
	}
}

void AFFGameSequence_Purchase::End()
{
	Super::End();
}

void AFFGameSequence_Purchase::OnValidate()
{

}

void AFFGameSequence_Purchase::OnCancel()
{

}

