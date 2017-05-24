// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubTurn.h"

#include "FFGameSequence_Fly.generated.h"

class AFFCameraActor;


UENUM()
enum class EFFFlyState : uint8
{
	Free,
	Mosey,
	FullBurn,
};

UENUM()
enum class EFFFlyOptions : uint8
{
	Mosey,
	FullBurn,
	Cancel,

	Count
};


UCLASS(minimalapi)
class AFFGameSequence_Fly : public AFFGameSequence_SubTurn
{
	GENERATED_BODY()

public:
	AFFGameSequence_Fly();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

protected:
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

	UFUNCTION()
	void OnFlyConfirmationAnswer(int32 id);

	virtual void ServerReceiveResponse(int32 res) override;

	virtual void Tick(float DeltaSeconds) override;
	
	void ShowZone();
	void HideZone();

	void ShowPaths(AFFSector* Dest);
	void HidePaths();

	UFUNCTION(Reliable, NetMulticast)
	void StartMosey(AFFSector* Dest);

	UFUNCTION(Reliable, NetMulticast)
	void StartFullBurn(AFFSector* Dest);

	void ReachDestination();

	void DrawNavigationCard();
	UFUNCTION()
	void OnDrawNavigationCardFinished(AFFGameSequence * Seq);

	virtual void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const override;


private:

	UPROPERTY()
	class UFFPathFinder* PathFinder;

	FFFPath Zone;
	FFFPath Path;

	UPROPERTY(Replicated)
	EFFFlyState State;

	UPROPERTY(Replicated)
	int32 MoveStep;

	UPROPERTY()
	AFFSector* ShipSector;

	UPROPERTY()
	AFFSector* Hover;

	UPROPERTY()
	AFFSector* Destination;

	UPROPERTY()
	AFFShip* Ship;

	UPROPERTY()
	AFFEngineCard* Engine;

	float m_fTime;
	float m_fDelay;
	
	UPROPERTY()
	class AFFGameSequence_Question* Confirmation;

	static char* s_sOptions[EFFFlyOptions::Count];
};



