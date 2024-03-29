// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubGame.h"

#include "FFGameSequence_GameTurns.generated.h"

class AFFCameraActor;

UCLASS(minimalapi)
class AFFGameSequence_GameTurns : public AFFGameSequence_SubGame
{
	GENERATED_BODY()

public:
	AFFGameSequence_GameTurns();
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	virtual bool IsCameraFree() const;

	bool IsTurnOf(int32 id) const;
	bool IsMyTurn() const;

	FFFPlayer& GetPlayingPlayer();
	const FFFPlayer& GetMyPlayer() const;

	void ConsumeAction(class AFFGameSequence_SubTurn* Action);
	
	void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const;

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void ServerReceiveResponse(int32 res) override;

	UFUNCTION(Reliable, NetMulticast)
	void StartPlayerTurn(int32 turn, int32 id);
	
	UFUNCTION(Reliable, NetMulticast)
	void FinishPlayerGameTurns(int32 id);

protected:
	// return true if capture the event
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

private:
	int32 CurrentPlayerId;
	int32 CurrentTurn;
	
	UPROPERTY()
	TArray<class AFFGameSequence_SubTurn*> CurrentActionDones;

	UPROPERTY(EditAnywhere)
	FString BoardCameraName;
};



