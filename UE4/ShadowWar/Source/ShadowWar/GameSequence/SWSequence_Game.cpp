// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWUtils.h"
#include "GSPlayerController.h"
#include "SWSequence_Game.h"
#include "GSSequence_Pause.h"
#include "UI/Page/SWGameHud.h"
#include "Game/SWUITuning.h"

#include "GSSequence_OneGameTurn_Base.h"
#include "SWSequence_Game/SWSequence_Setup.h"
#include "SWSequence_Game/SWSequence_Infiltration.h"
#include "SWSequence_Game/SWSequence_GameTurns.h"

class USWGameHud* ASWSequence_Game::GetGameHud()
{
	return GameHUD;
}


FSWPlayer& ASWSequence_Game::GetPlayer(int32 Id)
{
	check(Id >= 0 && Id < Players.Num());
	return Players[Id];
}

const FSWPlayer& ASWSequence_Game::GetPlayer(int32 Id) const
{
	check(Id >= 0 && Id < Players.Num());
	return Players[Id];
}

int32 ASWSequence_Game::GetPlayerCount() const
{
	return Players.Num();
}

void ASWSequence_Game::Start()
{
	AGSPlayerController* PlayerController = GetGSPlayerController();

	Super::Start();

	const USWUITuning* UITuning = GetDefaultUITuning();
	if (PlayerController && UITuning->GameHUDClass.GetDefaultObject())
	{
		GameHUD = CreateWidget<USWGameHud>(PlayerController, UITuning->GameHUDClass);
		GameHUD->AddToViewport();
		GameHUD->SetVisibility(ESlateVisibility::Visible);

		GameHUD->ClientId = PlayerController->GetId();
		GameHUD->PlayerId = PlayerController->GetId();
		GameHUD->Title = GetClass()->GetName();
		GameHUD->SetEndTurnButton(false);
	}

	if (IsServer())
	{
		for (TActorIterator<AGSPlayerController> It(GetWorld()); It; ++It)
		{
			FSWPlayer Player;
			Players.Add(Player);
		}

		AddSubSequence<AGSSequence_OneGameTurn_Base>(AGSSequence_OneGameTurn_Base::FInit(Players.Num(), ASWSequence_Setup::StaticClass()));
		AddSubSequence<AGSSequence_Pause>(AGSSequence_Pause::FInit(0.6f));
		AddSubSequence<ASWSequence_Infiltration>(this, &ASWSequence_Game::OnInfiltrationFinish);
		AddSubSequence<AGSSequence_Pause>(AGSSequence_Pause::FInit(0.6f));
		AddSubSequence<ASWSequence_GameTurns>();
		StartAllSubSequence();
	}
}

bool ASWSequence_Game::OnInfiltrationFinish(AGSSequence* Seq)
{
	return true;
}


void ASWSequence_Game::End()
{
	if (GameHUD != nullptr)
	{
		GameHUD->RemoveFromParent();
		GameHUD = nullptr;
	}

	Super::End();
}