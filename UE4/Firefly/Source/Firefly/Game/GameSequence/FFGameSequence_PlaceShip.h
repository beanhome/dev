// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubGame.h"

#include "FFGameSequence_PlaceShip.generated.h"

class AFFCameraActor;

UCLASS(minimalapi)
class AFFGameSequence_PlaceShip : public AFFGameSequence_SubGame
{
	GENERATED_BODY()

public:
	AFFGameSequence_PlaceShip();

	virtual bool IsCameraFree() const;

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void ServerReceiveResponse(int32 res) override;

	UFUNCTION(Reliable, NetMulticast)
	void StartPlayerPlaceShip(int32 id);
	
	UFUNCTION(Reliable, NetMulticast)
	void FinishPlayerPlaceShip(int32 id);

protected:
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

private:
	int32 CurrentPlayerId;

	class AFFSector* Hover;

	// server only
	int32 CurrentPlayerIndex;
	TArray<int32> PlayersOrder;

	UPROPERTY(EditAnywhere)
	FString CameraName;
};



