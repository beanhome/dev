// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "Actor/SWActor/SWFighter.h"
#include "Game/SWPlayerController.h"
#include "SWSequence_PrepareOneMove.h"
#include "GameSequence/Common/SWSequence_PlaceActor.h"
#include "Net/UnrealNetwork.h"

void ASWSequence_PrepareOneMove::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASWSequence_PrepareOneMove, Fighter);
}

void ASWSequence_PrepareOneMove::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
	
	if (IsClient())
		SetActorTickEnabled(true);
}

void ASWSequence_PrepareOneMove::Start()
{
	Super::Start();

	if (IsMyTurn())
	{
		check(Fighter != nullptr);
		Fighter->ShowMoveRange(true);
		Fighter->ShowGhost(true, false);
		Fighter->ActivateLimitation(true);
		StartLocalSubSequence<ASWSequence_PlaceActor>(ASWSequence_PlaceActor::StaticClass(), ASWSequence_PlaceActor::FInit((ASWActor*)Fighter->GetGhost(), Fighter), this, &ASWSequence_PrepareOneMove::OnEndPlaceSequences);
	}
}

void ASWSequence_PrepareOneMove::OnEndPlaceSequences(AGSSequence* Seq)
{
	check(IsClient());

	SendResponseToServer(FGSResponse());
}

void ASWSequence_PrepareOneMove::ServerReceiveResponse(FGSResponse res)
{
	ServerStopCurrentSequence();
}

void ASWSequence_PrepareOneMove::End()
{
	Super::End();

	if (IsMyTurn())
	{
		check(Fighter != nullptr);
		Fighter->ShowMoveRange(false);
		Fighter->ShowGhost(true, true);
		Fighter->ActivateLimitation(false);
	}
}

bool ASWSequence_PrepareOneMove::OnMouseEnterActor(int32 PlayerId, class AGSActor* Actor)
{
	//return IsTurnOf(PlayerId);
	return false;
}

bool ASWSequence_PrepareOneMove::OnMouseLeaveActor(int32 PlayerId, class AGSActor* Actor)
{
	//return IsTurnOf(PlayerId);
	return false;
}

bool ASWSequence_PrepareOneMove::OnMouseClickActor(int32 PlayerId, class AGSActor* Actor)
{
	/*
	if (IsServer() && IsTurnOf(PlayerId))// && Actor != Fighter)
	{
		ServerStopCurrentSequence();
		return true;
	}
	*/

	return IsTurnOf(PlayerId);
}

void ASWSequence_PrepareOneMove::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
