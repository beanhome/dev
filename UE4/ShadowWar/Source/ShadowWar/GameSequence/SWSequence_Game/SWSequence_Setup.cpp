// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "SWSequence_Setup.h"
#include "GameSequence/SWSequence_Game.h"
#include "GameSequence/Common/SWSequence_PlaceActor.h"
#include "Game/SWGameTuning.h"
#include "Actor/SWActor/SWFighter.h"
#include "Game/SWPlayerController.h"
#include "UI/Page/SWGameHud.h"

void ASWSequence_Setup::Start()
{
	Super::Start();

	if (IsClient())
	{
		ASWSequence_Game* SequenceOwner = GetOwner<ASWSequence_Game>();
		USWGameHud* Hud = (SequenceOwner ? SequenceOwner->GetGameHud() : nullptr);

		if (IsMyTurn())
		{
			if (Hud)
			{
				Hud->Title = TEXT("It is your turn, place your army");
				Hud->SetEndTurnButton(true, "End Setup");
				Hud->EndTurnDelegate.AddDynamic(this, &ASWSequence_Setup::OnClickEndTurn);
			}
		}
		else
		{
			if (Hud)
				Hud->Title = TEXT("Other Player Turn");
		}
	}
}

void ASWSequence_Setup::End()
{
	Super::End();

	ASWSequence_Game* SequenceOwner = GetOwner<ASWSequence_Game>();
	USWGameHud* Hud = (SequenceOwner ? SequenceOwner->GetGameHud() : nullptr);

	if (Hud)
		Hud->SetEndTurnButton(false);
}

bool ASWSequence_Setup::OnMouseClickActor(int32 PlayerId, class AGSActor* Actor)
{
	if (IsMyTurn())
	{
		ASWPlayerController* PlayerController = Cast<ASWPlayerController>(GetGSPlayerController());
		if (PlayerController != nullptr && PlayerController->HasCursorNavLocation())
		{
			FGSResponse res;
			res.Location = PlayerController->GetCursorNavLocation();

			SendResponseToServer(res);
		}
	}

	return false;
}

void ASWSequence_Setup::ServerReceiveResponse(FGSResponse res)
{
	check(IsServer());

	ASWFighter* Fighter = GetWorld()->SpawnActor<ASWFighter>(GetDefaultGameTuning()->FighterTemplate, res.Location, res.Rotation);

	StartSubSequence<ASWSequence_PlaceActor>(ASWSequence_PlaceActor::FInit(Fighter), this, &ASWSequence_Setup::OnEndPlaceSequences);
}

void ASWSequence_Setup::OnEndPlaceSequences(AGSSequence* Ses)
{
	//ServerStopCurrentSequence();
}

void ASWSequence_Setup::OnClickEndTurn()
{
	ClientStopSequence();
}