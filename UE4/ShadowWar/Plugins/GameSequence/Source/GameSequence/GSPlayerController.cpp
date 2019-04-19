// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GameSequence.h"
#include "GSPlayerController.h"

#include "UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Components/PrimitiveComponent.h"
#include "Materials/MaterialInstance.h"
#include "Engine/Engine.h"
#include "Engine/Canvas.h"

#include "GSGameState.h"

AGSPlayerController::AGSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

int32 AGSPlayerController::GetId() const
{
	return Id;
}

void AGSPlayerController::SetId(int32 id)
{
	Id = id;
}

AGSActor* AGSPlayerController::GetHoverActor() const
{
	return CurrentHoverActor;
}

UActorComponent* AGSPlayerController::GetHoverComponent() const
{
	return CurrentHoverComponent;
}

void AGSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(GameSequence, Log, TEXT("----------------  AGSPlayerController::BeginPlay %s %s"), *GetName(), *UEnum::GetValueAsString(TEXT("Engine.ENetRole"), Role));

	if (InputComponent)
	{
		InputComponent->BindAction("SelectActor", IE_Released, this, &AGSPlayerController::SelectActor);
	}
}

bool AGSPlayerController::IsActorInteractive() const
{
	AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
	return (GameState != nullptr && GameState->IsActorInteractive());
}

bool AGSPlayerController::IsSupportedForNetworking() const
{
	return true;
}

bool AGSPlayerController::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	return WroteSomething;
}

void AGSPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGSPlayerController, Id);
}

void AGSPlayerController::StartGame()
{

}

void AGSPlayerController::SendClientResponseToServer_Implementation(AGSSequence* seq, FGSResponse res)
{
	ensure(seq != nullptr);

	if (seq != nullptr)
		seq->ServerReceiveResponse(res);
}

bool AGSPlayerController::SendClientResponseToServer_Validate(AGSSequence* seq, FGSResponse res)
{
	return true;
}

void AGSPlayerController::SendClientStopSequenceToServer_Implementation(AGSSequence* seq)
{
	seq->ServerStopCurrentSequence();
}

bool AGSPlayerController::SendClientStopSequenceToServer_Validate(AGSSequence* seq)
{
	return true;
}

void AGSPlayerController::SendClientStateToServer_Implementation(AGSSequence* seq, EGSClientState state)
{
	ensure(seq != nullptr);

	if (seq != nullptr)
	{
		seq->ServerReceiveClientState(GetId(), state);
	}
}

bool AGSPlayerController::SendClientStateToServer_Validate(AGSSequence* seq, EGSClientState state)
{
	return true;
}


bool AGSPlayerController::SendClientMouseEnterActor_Validate(class AGSActor* Actor)
{
	return true;
}

bool AGSPlayerController::SendClientMouseLeaveActor_Validate(class AGSActor* Actor)
{
	return true;
}

bool AGSPlayerController::SendClientMouseClickActor_Validate(class AGSActor* Actor)
{
	return true;
}

void AGSPlayerController::SendClientMouseEnterActor_Implementation(class AGSActor* Actor)
{
	AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
	if (GameState != nullptr && GameState->Main != nullptr)
		GameState->Main->ReceiveMouseEnterActor(Id, Actor);
}

void AGSPlayerController::SendClientMouseLeaveActor_Implementation(class AGSActor* Actor)
{
	AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
	if (GameState != nullptr && GameState->Main != nullptr)
		GameState->Main->ReceiveMouseLeaveActor(Id, Actor);
}

void AGSPlayerController::SendClientMouseClickActor_Implementation(class AGSActor* Actor)
{
	AGSGameState* GameState = GetWorld()->GetGameState<AGSGameState>();
	if (GameState != nullptr && GameState->Main != nullptr)
		GameState->Main->ReceiveMouseClickActor(Id, Actor);
}

/*
bool AGSPlayerController::SendClientValidateToServer_Validate(class AGSSequence_SubTurn* Seq)
{
	return true;
}

void AGSPlayerController::SendClientValidateToServer_Implementation(class AGSSequence_SubTurn* Seq)
{
	ensure(Seq != nullptr);

	if (Seq != nullptr)
		Seq->ClientValidate();
}

bool AGSPlayerController::SendClientCancelToServer_Validate(class AGSSequence_SubTurn* Seq)
{
	return true;
}

void AGSPlayerController::SendClientCancelToServer_Implementation(class AGSSequence_SubTurn* Seq)
{
	ensure(Seq != nullptr);

	if (Seq != nullptr)
		Seq->ClientCancel();
}
*/

void AGSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	if (IsActorInteractive())
	{
		FCollisionObjectQueryParams ObjectQueryParams;


		FVector MouseLocation, MouseDirection;
		if (DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
		{
			FVector Start = MouseLocation;
			FVector End = MouseLocation + MouseDirection * 5000.f;

			bool bHit = GetWorld()->LineTraceSingleByObjectType(HoverActorHit, Start, End, ObjectQueryParams);
			AGSActor* HoverActor = (bHit ? Cast<AGSActor>(HoverActorHit.Actor.Get()) : nullptr);
			CurrentHoverComponent = (bHit ? HoverActorHit.Component.Get() : nullptr);
			//UE_LOG(GameSequence, Log, TEXT("Object : %s"), *Hit.Actor->GetName());

			if (CurrentHoverActor != HoverActor)
			{
				if (CurrentHoverActor != nullptr)
				{
					CurrentHoverActor->OnMouseLeave();
					CurrentHoverActor = nullptr;
				}

				if (HoverActor != nullptr)
				{
					CurrentHoverActor = HoverActor;
					CurrentHoverActor->OnMouseEnter();
				}
			}
		}
	}
}

void AGSPlayerController::DrawDebug(class UCanvas* Canvas, float& x, float& y) const
{
	y += 10.f;

	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColor::White);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("Player %d"), Id), x, y);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("Current HoverActor %s"), (CurrentHoverActor == nullptr ? TEXT("none") : *CurrentHoverActor->GetName())), x, y);
}


void AGSPlayerController::SelectActor()
{
	if (IsActorInteractive())
	{
		if (CurrentHoverActor == nullptr)
			SendClientMouseClickActor(nullptr);
		else
			CurrentHoverActor->OnMouseClick();
	}
}

void AGSPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
}
bool AGSPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}

bool AGSPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	return Super::InputTouch(Handle, Type, TouchLocation, DeviceTimestamp, TouchpadIndex);
}

bool AGSPlayerController::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	return Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
}
