// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_SubTurn.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_GameTurns.h"
#include "UI/Page/FFSpecificHud.h"

AFFGameSequence_SubTurn::AFFGameSequence_SubTurn()
{
}

AFFGameSequence_Game* AFFGameSequence_SubTurn::GetGame() const
{
	return GetOwner<AFFGameSequence_Game>();
}

UFFGameHud* AFFGameSequence_SubTurn::GetHud() const
{
	return GetGame()->GetGameHud();
}

const FFFPlayer& AFFGameSequence_SubTurn::GetPlayer(int32 id) const
{
	return GetGame()->GetPlayer(id);
}

const FFFPlayer& AFFGameSequence_SubTurn::GetPlayingPlayer() const
{
	return GetOwner<AFFGameSequence_GameTurns>()->GetPlayingPlayer();
}

bool AFFGameSequence_SubTurn::IsTurnOf(int32 id) const
{
	return GetOwner<AFFGameSequence_GameTurns>()->IsTurnOf(id);
}

bool AFFGameSequence_SubTurn::IsMyTurn() const
{
	return GetOwner<AFFGameSequence_GameTurns>()->IsMyTurn();
}

void AFFGameSequence_SubTurn::ConsumeAction()
{
	check(IsLocal() == false);

	if (IsClient())
	{
		GetFFPlayerController()->ConsumeAction(this);
	}
	else
	{
		GetOwner<AFFGameSequence_GameTurns>()->ConsumeAction(this);
	}
}

void AFFGameSequence_SubTurn::Start()
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	Super::Start();

	if (PlayerController && SpecificHudClass.GetDefaultObject())
	{
		SpecificHud = CreateWidget<UFFSpecificHud>(PlayerController, SpecificHudClass);
		SpecificHud->AddToViewport();
		SpecificHud->SetVisibility(ESlateVisibility::Visible);

		SpecificHud->ValidateDelegate.AddDynamic(this, &AFFGameSequence_SubTurn::SendValidateToServer);
		SpecificHud->CancelDelegate.AddDynamic(this, &AFFGameSequence_SubTurn::SendCancelToServer);
	}
}

void AFFGameSequence_SubTurn::End()
{
	Super::End();

	if (SpecificHud)
	{
		SpecificHud->RemoveFromParent();
		SpecificHud = nullptr;
	}
}

void AFFGameSequence_SubTurn::SendValidateToServer()
{
	check(IsClient());
	GetFFPlayerController()->SendClientValidateToServer(this);
}

void AFFGameSequence_SubTurn::SendCancelToServer()
{
	check(IsClient());
	GetFFPlayerController()->SendClientCancelToServer(this);
}

void AFFGameSequence_SubTurn::ClientValidate_Implementation()
{
	OnValidate();
}

void AFFGameSequence_SubTurn::ClientCancel_Implementation()
{
	OnCancel();
}

void AFFGameSequence_SubTurn::OnValidate()
{
}

void AFFGameSequence_SubTurn::OnCancel()
{
}
