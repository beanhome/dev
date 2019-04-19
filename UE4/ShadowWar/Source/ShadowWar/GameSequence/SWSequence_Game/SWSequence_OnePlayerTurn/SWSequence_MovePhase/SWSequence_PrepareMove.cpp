// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "Actor/SWActor/SWFighter.h"
#include "Actor/SWActor/SWGhost.h"
#include "GSPlayerController.h"
#include "SWSequence_PrepareMove.h"
#include "SWSequence_PrepareMove/SWSequence_PrepareOneMove.h"

void ASWSequence_PrepareMove::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void ASWSequence_PrepareMove::Start()
{
	Super::Start();
}

void ASWSequence_PrepareMove::End()
{
	Super::End();
}

void ASWSequence_PrepareMove::Suspend()
{
	Super::Suspend();
}

void ASWSequence_PrepareMove::Resume()
{
	Super::Resume();

	if (IsClient())
		RefreshHoverFighter();
}



bool ASWSequence_PrepareMove::OnMouseEnterActor(int32 PlayerId, class AGSActor* Actor)
{
	if (IsClient() && IsTurnOf(PlayerId))
	{
		ASWFighter* Fighter = Cast<ASWFighter>(Actor);
		ASWGhost* Ghost = Cast<ASWGhost>(Actor);

		if (Fighter == nullptr && Ghost != nullptr)
			Fighter = Ghost->GetFighter();

		if (Fighter != nullptr)
		{
			Ghost = Fighter->GetGhost();

			if (HoverFighter != nullptr && HoverFighter != Fighter)
			{
				HoverFighter->SetOutline(false);
				//if (Ghost != nullptr)
				//	Ghost->SetOutline(false);
			}

			HoverFighter = Fighter;
			HoverFighter->SetOutline(true, 2);
			//if (Ghost != nullptr)
			//	Ghost->SetOutline(true, 2);
		}
	}

	return false;
}

bool ASWSequence_PrepareMove::OnMouseLeaveActor(int32 PlayerId, class AGSActor* Actor)
{
	if (IsClient() && IsTurnOf(PlayerId))
	{
		ASWFighter* Fighter = Cast<ASWFighter>(Actor);
		ASWGhost* Ghost = Cast<ASWGhost>(Actor);

		if (Fighter == nullptr && Ghost != nullptr)
			Fighter = Ghost->GetFighter();

		if (Fighter != nullptr && Fighter == HoverFighter)
		{
			HoverFighter->SetOutline(false);
			//if (Ghost != nullptr)
			//	Ghost->SetOutline(false);
			HoverFighter = nullptr;
		}
	}

	return false;
}

bool ASWSequence_PrepareMove::OnMouseClickActor(int32 PlayerId, class AGSActor* Actor)
{
	ASWFighter* Fighter = Cast<ASWFighter>(Actor);
	ASWGhost* Ghost = Cast<ASWGhost>(Actor);

	if (Fighter == nullptr && Ghost != nullptr)
		Fighter = Ghost->GetFighter();

	if (IsServer())
	{
		if (Fighter != nullptr)
		{
			ASWSequence_PrepareOneMove* Seq = StartSubSequence<ASWSequence_PrepareOneMove>();
			Seq->Fighter = Fighter;
		}
		else
		{
			ServerStopCurrentSequence();
		}
	}

	return false;
}


void ASWSequence_PrepareMove::RefreshHoverFighter()
{
	check(IsClient());

	ASWFighter* Fighter = Cast<ASWFighter>(GetGSPlayerController()->GetHoverActor());

	if (Fighter != HoverFighter)
	{
		if (HoverFighter != nullptr)
			HoverFighter->SetOutline(false);

		HoverFighter = Fighter;
		if (HoverFighter != nullptr)
			HoverFighter->SetOutline(true, 2);
	}
}

void ASWSequence_PrepareMove::Tick(float DeltaSeconds)
{
	if (HoverFighter != nullptr && HoverFighter->GetGhost() != nullptr && HoverFighter->GetGhost()->bHidden == false)
	{
		DrawDebugLine(GetWorld(), HoverFighter->GetActorLocation(), HoverFighter->GetGhost()->GetActorLocation(), FColor::Blue, false, -1.f, 0, 2.f);
	}
}
