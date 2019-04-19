// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowWar.h"
#include "Actor/SWActor.h"
#include "Game/SWPlayerController.h"
#include "SWSequence_PlaceActor.h"
#include "Net/UnrealNetwork.h"

void ASWSequence_PlaceActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASWSequence_PlaceActor, Actor);
}

void ASWSequence_PlaceActor::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
	
	if (IsClient())
		SetActorTickEnabled(true);

	if (InitParameter != nullptr)
	{
		Actor = ((ASWSequence_PlaceActor::FInit*)InitParameter)->Actor;
		LimitationActors = ((ASWSequence_PlaceActor::FInit*)InitParameter)->LimitationActors;
	}
}

void ASWSequence_PlaceActor::Start()
{
	Super::Start();

	if (IsMyTurn())
	{
		if (Actor != nullptr)
		{
			Phase = EPhase::Place;
			Actor->SetOutline(true, 2);
			Actor->SetActorEnableCollision(false);
		}

		// todo: save a restore
	}
}

void ASWSequence_PlaceActor::OnRep_Actor(class ASWActor* _Actor)
{
	if (Actor != nullptr)
	{
		Phase = EPhase::Place;
		Actor->SetOutline(true, 2);
		Actor->SetActorEnableCollision(false);
	}
}

void ASWSequence_PlaceActor::End()
{
	Super::End();

	if (IsMyTurn())
	{
		check(Actor != nullptr);
		Actor->SetOutline(false);
		Actor->SetActorEnableCollision(true);
	
		// todo: save a restore
	}
}

bool ASWSequence_PlaceActor::OnMouseEnterActor(int32 PlayerId, class AGSActor* GSActor)
{
	return false;
}

bool ASWSequence_PlaceActor::OnMouseLeaveActor(int32 PlayerId, class AGSActor* GSActor)
{
	return false;
}

bool ASWSequence_PlaceActor::OnMouseClickActor(int32 PlayerId, class AGSActor* GSActor)
{
	if (IsMyTurn())
	{
		switch (Phase)
		{
			case EPhase::Place:
				Phase = EPhase::Rotate;
				break;

			case EPhase::Rotate:
				if (IsClient())
				{
					FGSResponse res;
					res.Location = Actor->GetActorLocation();
					res.Rotation = Actor->GetActorRotation();
					SendResponseToServer(res);
				}
				else if (IsLocal())
				{
					LocalStopCurrentSequence();
				}
				break;
		}

		return true;
	}

	return IsTurnOf(PlayerId);
}

void ASWSequence_PlaceActor::ServerReceiveResponse(FGSResponse res)
{
	check(IsServer());
	
	Actor->SetActorLocation(res.Location);
	Actor->SetActorRotation(res.Rotation);
	ServerStopCurrentSequence();
}


void ASWSequence_PlaceActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsMyTurn() == false)
		return;

	if (Actor == nullptr)
		return;

	ASWPlayerController* PlayerController = Cast<ASWPlayerController>(GetGSPlayerController());
	if (PlayerController == nullptr)
		return;

	switch (Phase)
	{
		case EPhase::Place:
		{
			if (PlayerController->HasCursorNavLocation())
			{
				FVector CursorLocation = PlayerController->GetCursorNavLocation();
				FVector ActorLocation = Actor->GetActorLocation();
				FVector Offset = CursorLocation - ActorLocation;

				bool bIsInside = true;

				if (LimitationActors.Num() > 0)
				{
					bIsInside = false;

					TArray<struct FOverlapResult> OutOverlaps;
					FCollisionObjectQueryParams QueryParam;
					GetWorld()->OverlapMultiByObjectType(OutOverlaps, CursorLocation, FQuat::Identity, QueryParam, FCollisionShape::MakeSphere(1.f));
					for (const FOverlapResult& Result : OutOverlaps)
					{
						if (LimitationActors.Contains(Result.Actor))
						{
							bIsInside = true;
							break;
						}
					}
				}

				if (bIsInside)
					Actor->SetActorLocation(CursorLocation);
			}
			break;
		}

		case EPhase::Rotate:
		{
			if (PlayerController->HasCursorGroundLocation())
			{
				FVector CursorLocation = PlayerController->GetCursorGroundLocation();
				FVector ActorLocation = Actor->GetActorLocation();
				FVector Offset = CursorLocation - ActorLocation;
				Offset.Z = 0.f;
				FRotator Rot = Offset.Rotation();
				Rot.Pitch = Rot.Roll = 0.f;

				Actor->SetActorRotation(Rot);
			}
			break;
		}
	}
}
