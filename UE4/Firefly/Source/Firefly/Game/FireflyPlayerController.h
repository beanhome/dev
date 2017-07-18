// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Game/GameSequence/FFGameSequence.h"
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

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;


	int32 GetId() const;
	void SetId(int32 id);

	void MoveUpInput(float Val);
	void MoveRightInput(float Val);

	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad);
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex);
	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad);

	AFFActor* GetHoverActor() const;
	UActorComponent* GetHoverComponent() const;

	bool IsCameraFree() const;
	bool IsActorInteractive() const;

	const UFFCameraManager* GetCameraManager() const;
	AFFCameraActor* GetCurrentCamera() const;
	void JumpToCamera(AFFCameraActor*, bool bForce = false);
	void JumpToMainCamera(bool bForce = false);

	void DrawDebug(class UCanvas* Canvas, float& x, float& y) const;

	UFUNCTION(Reliable, Client)
	void NotifySetHost();

	UFUNCTION(Reliable, Client)
	void NotifySetGuest();

	UFUNCTION(Reliable, Client)
	void NotifyNewPlayer(APlayerController* NewPlayer);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerLaunchGame();

	UFUNCTION(Reliable, Client)
	void StartGame();

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientResponseToServer(AFFGameSequence* seq, int32 res);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientStateToServer(AFFGameSequence* seq, EFFClientGameSeqState state);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientMouseEnterActor(class AFFActor* Actor);
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientMouseLeaveActor(class AFFActor* Actor);
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientMouseClickActor(class AFFActor* Actor);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientValidateToServer(class AFFGameSequence_SubTurn* Seq);
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientCancelToServer(class AFFGameSequence_SubTurn* Seq);

	UFUNCTION(Reliable, Server, WithValidation)
	void ConsumeAction(class AFFGameSequence_SubTurn* Action);

	//UFUNCTION(Reliable, Server, WithValidation)
	//void StopCurrentSequence();

	//UFUNCTION(Reliable, Client)
	//void Message(UFFMessage* Msg);

private:
	void CreateLobbyPage();
	void SelectActor();

private:
	UPROPERTY(Replicated)
	int32 Id;

	UPROPERTY()
	UFFCameraManager* CameraManager;

	UPROPERTY()
	UFFLobbyPage* LobbyPage;

	UPROPERTY()
	UFFWaitingPage* WaitingPage;

	UPROPERTY()
	AFFActor* CurrentHoverActor;

	UPROPERTY()
	UActorComponent* CurrentHoverComponent;
};


