// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
#include "GSSequence.h"
#include "GSPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS(Blueprintable)
class GAMESEQUENCE_API AGSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGSPlayerController();

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	int32 GetId() const;
	void SetId(int32 id);

	void StartGame();

	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;

	AGSActor* GetHoverActor() const;
	UActorComponent* GetHoverComponent() const;

	bool IsActorInteractive() const;

	void DrawDebug(class UCanvas* Canvas, float& x, float& y) const;

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientResponseToServer(AGSSequence* seq, FGSResponse res);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientStopSequenceToServer(AGSSequence* seq);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientStateToServer(AGSSequence* seq, EGSClientState state);

	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientMouseEnterActor(class AGSActor* Actor);
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientMouseLeaveActor(class AGSActor* Actor);
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientMouseClickActor(class AGSActor* Actor);

	/*
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientValidateToServer(class AGSSequence_SubTurn* Seq);
	UFUNCTION(Reliable, Server, WithValidation)
	void SendClientCancelToServer(class AGSSequence_SubTurn* Seq);
	*/

private:
	void SelectActor();

private:
	UPROPERTY(Replicated)
	int32 Id;

protected:
	UPROPERTY()
	FHitResult HoverActorHit;

	UPROPERTY()
	AGSActor* CurrentHoverActor;

	UPROPERTY()
	UActorComponent* CurrentHoverComponent;

};


