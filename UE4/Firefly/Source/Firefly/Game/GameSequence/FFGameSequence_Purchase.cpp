// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Purchase.h"
#include "UI/Page/FFPurchasePopup.h"
#include "Board/FFShipBoard.h"

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
		PurchasePopup->SetCash(GetPlayingPlayer().Credits);
	}
}

void AFFGameSequence_Purchase::End()
{
	Super::End();
}

void AFFGameSequence_Purchase::OnValidate()
{
	if (IsServer())
	{
		int32 iCost = 0;

		const FFFPlayer& Player = GetPlayingPlayer();

		UFFPurchasePopup* PurchasePopup = Cast<UFFPurchasePopup>(SpecificHud);
		const TArray<struct FFFPurchaseStuff>& PurchaseStuffs = PurchasePopup->GetPurchaseStuff();
		for (const FFFPurchaseStuff& Stuff : PurchaseStuffs)
			iCost += Stuff.Count * Stuff.Price;

		if (iCost > 0 && iCost <= Player.Credits)
		{
			// todo test capacity and send error message

			for (const FFFPurchaseStuff& Stuff : PurchaseStuffs)
				Player.ShipBoard->AddStuff(Stuff.Stuff, Stuff.Count);
			
			ServerStopCurrentSequence();
		}
		else
		{
			// Send Error message
		}
	}

}

void AFFGameSequence_Purchase::OnCancel()
{
	if (IsServer())
		ServerStopCurrentSequence();
}

