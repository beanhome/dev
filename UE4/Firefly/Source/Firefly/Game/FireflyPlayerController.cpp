// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FireflyPlayerController.h"
#include "Game/FFUITuning.h"
#include "UI/Page/FFLobbyPage.h"
#include "UI/Page/FFWaitingPage.h"

#include "UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "Camera/FFCameraManager.h"
#include "FireflyGameMode.h"

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
	}
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



void AFireflyPlayerController::StartGame_Implementation(int32 id)
{
	Id = id;

	UE_LOG(Firefly, Log, TEXT("  **********   AFireflyPlayerController::StartGame_Implementation Controller %s (World %x)"), *GetName(), GetWorld());

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

bool AFireflyPlayerController::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	return WroteSomething;
}

/*
void AFireflyPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
}
*/

/*
void AFireflyPlayerController::Message_Implementation(UFFMessage* Msg)
{

}
*/

void AFireflyPlayerController::SendResponseToServer_Implementation(int32 res)
{
	AFFGameState* GameState = GetWorld()->GetGameState<AFFGameState>();
	GameState->Game->ServerReceiveResponse(res);
}

bool AFireflyPlayerController::SendResponseToServer_Validate(int32 res)
{
	return true;
}

void AFireflyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	//CameraManager->Update(DeltaTime);


	FCollisionObjectQueryParams ObjectQueryParams;

	FHitResult Hit;

	FVector MouseLocation, MouseDirection;
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	FVector Start = MouseLocation;
	FVector End = MouseLocation + MouseDirection * 5000.f;

	bool res = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	AFFActor* HoverActor = (res ? Cast<AFFActor>(Hit.Actor.Get()) : nullptr);

	//UE_LOG(Firefly, Log, TEXT("Object : %s"), *Hit.Actor->GetName());

	if (CurrentHoverActor != HoverActor)
	{
		if (CurrentHoverActor != nullptr)
		{
			CurrentHoverActor->OnMouseExit();
			CurrentHoverActor = nullptr;
		}

		if (HoverActor != nullptr)
		{
			CurrentHoverActor = HoverActor;
			CurrentHoverActor->OnMouseEnter();
		}
	}
}

const UFFCameraManager* AFireflyPlayerController::GetCameraManager() const
{
	return CameraManager;
}

AFFCameraActor* AFireflyPlayerController::GetCurrentCamera() const
{
	return CameraManager->GetCurrentCamera();
}

void AFireflyPlayerController::JumpToCamera(AFFCameraActor* Camera)
{
	if (CameraManager != nullptr)
		CameraManager->JumpToCamera(Camera);
}

void AFireflyPlayerController::JumpToMainCamera()
{
	if (CameraManager != nullptr)
		CameraManager->JumpToMainCamera();
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
	if (Key == EKeys::RightMouseButton)
	{
		JumpToMainCamera();
	}
	else if (Key == EKeys::LeftMouseButton)
	{
		if (CurrentHoverActor != nullptr)
			CurrentHoverActor->OnMouseClick();
	}

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
