// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FireflyPlayerController.h"
#include "Game/FFUITuning.h"
#include "UI/Page/FFLobbyPage.h"
#include "UI/Page/FFWaitingPage.h"

#include "UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Camera/FFCameraManager.h"
#include "FFGameState.h"
#include "FireflyGameMode.h"

#include "Game/GameSequence/FFGameSequence_GameTurns.h"

AFireflyPlayerController::AFireflyPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	if (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() == nullptr)
		CameraManager = CreateDefaultSubobject<UFFCameraManager>(TEXT("FFCameraManager"));
}

int32 AFireflyPlayerController::GetId() const
{
	return Id;
}

void AFireflyPlayerController::SetId(int32 id)
{
	Id = id;
}

AFFActor* AFireflyPlayerController::GetHoverActor() const
{
	return CurrentHoverActor;
}

UActorComponent* AFireflyPlayerController::GetHoverComponent() const
{
	return CurrentHoverComponent;
}

void AFireflyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(Firefly, Log, TEXT("----------------  AFireflyPlayerController::BeginPlay %s %s"), *GetName(), *UEnum::GetValueAsString(TEXT("Engine.ENetRole"), Role));

	if (InputComponent)
	{
		// Bind our control axis' to callback functions
		InputComponent->BindAxis("MoveUp", this, &AFireflyPlayerController::MoveUpInput);
		InputComponent->BindAxis("MoveRight", this, &AFireflyPlayerController::MoveRightInput);
		InputComponent->BindAction("NextCamera", IE_Pressed, CameraManager, &UFFCameraManager::JumpNextCamera);
		InputComponent->BindAction("PrevCamera", IE_Pressed, CameraManager, &UFFCameraManager::JumpPrevCamera);
		InputComponent->BindAction("SelectActor", IE_Released, CameraManager, &UFFCameraManager::JumpToActorCamera);
		InputComponent->BindAction("MainCamera", IE_Released, CameraManager, &UFFCameraManager::JumpToMainCamera);
	
		InputComponent->BindAction("SelectActor", IE_Released, this, &AFireflyPlayerController::SelectActor);
	}
}

bool AFireflyPlayerController::IsCameraFree() const
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	return (GameState != nullptr && GameState->IsCameraFree());
}

bool AFireflyPlayerController::IsActorInteractive() const
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	return (GameState != nullptr && GameState->IsActorInteractive());
}


void AFireflyPlayerController::CreateLobbyPage()
{
	const UFFUITuning* UITuning = GetDefaultUITuning();
	LobbyPage = CreateWidget<UFFLobbyPage>(this, UITuning->LobbyPageClass);
	LobbyPage->AddToViewport();
	LobbyPage->SetVisibility(ESlateVisibility::Visible);
}

void AFireflyPlayerController::NotifySetHost_Implementation()
{
	if (LobbyPage == nullptr)
		CreateLobbyPage();
}

void AFireflyPlayerController::NotifySetGuest_Implementation()
{
	if (WaitingPage == nullptr)
	{
		const UFFUITuning* UITuning = GetDefaultUITuning();
		WaitingPage = CreateWidget<UFFWaitingPage>(this, UITuning->WaitingPageClass);
		WaitingPage->AddToViewport();
		WaitingPage->SetVisibility(ESlateVisibility::Visible);
	}
}

void AFireflyPlayerController::NotifyNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (LobbyPage == nullptr)
		CreateLobbyPage();

	if (NewPlayer != nullptr)
		LobbyPage->AddPlayer(NewPlayer->GetName());
}

void AFireflyPlayerController::ServerLaunchGame_Implementation()
{
	AFireflyGameMode* const GameMode = GetWorld()->GetAuthGameMode<AFireflyGameMode>();

	GameMode->StartGame();
}

bool AFireflyPlayerController::ServerLaunchGame_Validate()
{
	return true;
}



void AFireflyPlayerController::StartGame_Implementation()
{
	UE_LOG(Firefly, Log, TEXT("  **********   AFireflyPlayerController::StartGame_Implementation %d"), Id);

	if (LobbyPage != nullptr)
	{
		LobbyPage->RemoveFromParent();
		LobbyPage = nullptr;
	}

	if (WaitingPage != nullptr)
	{
		WaitingPage->RemoveFromParent();
		WaitingPage = nullptr;
	}
}


bool AFireflyPlayerController::IsSupportedForNetworking() const
{
	return true;
}

bool AFireflyPlayerController::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	return WroteSomething;
}

void AFireflyPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireflyPlayerController, Id);
}

/*
void AFireflyPlayerController::Message_Implementation(UFFMessage* Msg)
{
}
*/

void AFireflyPlayerController::SendClientResponseToServer_Implementation(AFFGameSequence* seq, int32 res)
{
	ensure(seq != nullptr);

	if (seq != nullptr)
		seq->ServerReceiveResponse(res);
}

bool AFireflyPlayerController::SendClientResponseToServer_Validate(AFFGameSequence* seq, int32 res)
{
	return true;
}

void AFireflyPlayerController::SendClientStateToServer_Implementation(AFFGameSequence* seq, EFFClientGameSeqState state)
{
	ensure(seq != nullptr);

	if (seq != nullptr)
	{
		seq->ServerReceiveClientState(GetId(), state);
	}
}

bool AFireflyPlayerController::SendClientStateToServer_Validate(AFFGameSequence* seq, EFFClientGameSeqState state)
{
	return true;
}


bool AFireflyPlayerController::SendClientMouseEnterActor_Validate(class AFFActor* Actor)
{
	return true;
}

bool AFireflyPlayerController::SendClientMouseLeaveActor_Validate(class AFFActor* Actor)
{
	return true;
}

bool AFireflyPlayerController::SendClientMouseClickActor_Validate(class AFFActor* Actor)
{
	return true;
}

void AFireflyPlayerController::SendClientMouseEnterActor_Implementation(class AFFActor* Actor)
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
		GameState->Game->ReceiveMouseEnterActor(Id, Actor);
}

void AFireflyPlayerController::SendClientMouseLeaveActor_Implementation(class AFFActor* Actor)
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
		GameState->Game->ReceiveMouseLeaveActor(Id, Actor);
}

void AFireflyPlayerController::SendClientMouseClickActor_Implementation(class AFFActor* Actor)
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
		GameState->Game->ReceiveMouseClickActor(Id, Actor);
}

bool AFireflyPlayerController::ConsumeAction_Validate(class AFFGameSequence_SubTurn* Action)
{
	return true;
}

void AFireflyPlayerController::ConsumeAction_Implementation(class AFFGameSequence_SubTurn* Action)
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	if (GameState != nullptr && GameState->Game != nullptr)
	{
		AFFGameSequence_GameTurns* GameTurns = GameState->Game->FindSubSequence<AFFGameSequence_GameTurns>();
	}
}

bool AFireflyPlayerController::SendClientValidateToServer_Validate(class AFFGameSequence_SubTurn* Seq)
{
	return true;
}

void AFireflyPlayerController::SendClientValidateToServer_Implementation(class AFFGameSequence_SubTurn* Seq)
{
	ensure(Seq != nullptr);

	if (Seq != nullptr)
		Seq->ClientValidate();
}

bool AFireflyPlayerController::SendClientCancelToServer_Validate(class AFFGameSequence_SubTurn* Seq)
{
	return true;
}

void AFireflyPlayerController::SendClientCancelToServer_Implementation(class AFFGameSequence_SubTurn* Seq)
{
	ensure(Seq != nullptr);

	if (Seq != nullptr)
		Seq->ClientCancel();
}

void AFireflyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	//CameraManager->Update(DeltaTime);

	if (IsActorInteractive())
	{
		FCollisionObjectQueryParams ObjectQueryParams;

		FHitResult Hit;

		FVector MouseLocation, MouseDirection;
		if (DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
		{
			FVector Start = MouseLocation;
			FVector End = MouseLocation + MouseDirection * 5000.f;

			bool res = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

			AFFActor* HoverActor = (res ? Cast<AFFActor>(Hit.Actor.Get()) : nullptr);
			CurrentHoverComponent = (res ? Hit.Component.Get() : nullptr);
			//UE_LOG(Firefly, Log, TEXT("Object : %s"), *Hit.Actor->GetName());

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

void AFireflyPlayerController::DrawDebug(class UCanvas* Canvas, float& x, float& y) const
{
	y += 10.f;

	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColor::White);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("Player %d"), Id), x, y);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("Current HoverActor %s"), (CurrentHoverActor == nullptr ? TEXT("none") : *CurrentHoverActor->GetName())), x, y);
}


void AFireflyPlayerController::SelectActor()
{
	if (IsActorInteractive() && CurrentHoverActor != nullptr)
		CurrentHoverActor->OnMouseClick();
}


const UFFCameraManager* AFireflyPlayerController::GetCameraManager() const
{
	return CameraManager;
}

AFFCameraActor* AFireflyPlayerController::GetCurrentCamera() const
{
	return CameraManager->GetCurrentCamera();
}

void AFireflyPlayerController::JumpToCamera(AFFCameraActor* Camera, bool bForce)
{
	if (CameraManager != nullptr)
		CameraManager->JumpToCamera(Camera, bForce);
}

void AFireflyPlayerController::JumpToMainCamera(bool bForce)
{
	if (CameraManager != nullptr)
		CameraManager->JumpToMainCamera(bForce);
}

void AFireflyPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	if (CameraManager != nullptr)
		CameraManager->ApplyInput(DeltaTime, InputComponent);
}

void AFireflyPlayerController::MoveUpInput(float Val)
{
}

void AFireflyPlayerController::MoveRightInput(float Val)
{
}

bool AFireflyPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}

bool AFireflyPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	return Super::InputTouch(Handle, Type, TouchLocation, DeviceTimestamp, TouchpadIndex);
}

bool AFireflyPlayerController::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	return Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
}
