// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "FireflyPlayerController.generated.h"

class UFFLobbyPage;
class UFFWaitingPage;
class AFFCameraActor;
class UFFCameraManager;

/** PlayerController class used to enable cursor */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFireflyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFireflyPlayerController();

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	int32 GetId() const;
	void SetId(int32 id);

	void MoveUpInput(float Val);
	void MoveRightInput(float Val);

	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad);
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex);
	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad);
	
	const UFFCameraManager* GetCameraManager() const;
	AFFCameraActor* GetCurrentCamera() const;
	void JumpToCamera(AFFCameraActor*);
	void JumpToMainCamera();

	UFUNCTION(Reliable, Client)
	void NotifySetHost();

	UFUNCTION(Reliable, Client)
	void NotifySetGuest();

	UFUNCTION(Reliable, Client)
	void NotifyNewPlayer(APlayerController* NewPlayer);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerLaunchGame();

	UFUNCTION(Reliable, Client)
	void StartGame(int32 id);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendResponseToServer(int32 res);

	//UFUNCTION(Reliable, Server, WithValidation)
	//void StopCurrentSequence();

	//UFUNCTION(Reliable, Client)
	//void Message(UFFMessage* Msg);

private:
	void CreateLobbyPage();

private:
	UPROPERTY()
	int32 Id;

	UPROPERTY()
	UFFCameraManager* CameraManager;

	UPROPERTY()
	UFFLobbyPage* LobbyPage;

	UPROPERTY()
	UFFWaitingPage* WaitingPage;

	UPROPERTY()
	AFFActor* CurrentHoverActor;
};


