// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubGame.h"

#include "FFGameSequence_ChooseLeaderAndShip.generated.h"

class UFFFreeAction;
UCLASS(minimalapi)
class AFFGameSequence_ChooseLeaderAndShip : public AFFGameSequence_SubGame
{
	GENERATED_BODY()

public:
	AFFGameSequence_ChooseLeaderAndShip();

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void ServerReceiveResponse(int32 res) override;

	UFUNCTION(Reliable, NetMulticast)
	void StartPlayerChooseLeader(int32 id, const TArray<TSubclassOf<AFFActor>>& NewLeaderCards);
	
	UFUNCTION(Reliable, NetMulticast)
	void FinishPlayerChooseLeader(int32 id);

	UFUNCTION(Reliable, NetMulticast)
	void StartPlayerChooseShip(int32 id, const TArray<TSubclassOf<AFFActor>>& NewShips);

	UFUNCTION(Reliable, NetMulticast)
	void FinishPlayerChooseShip(int32 id);

	enum class EFFPhase : uint8
	{
		Leader,
		Ship,
	};

private:
	UFUNCTION()
	void OnLeaderCardChoosen(int32 id);
	UFUNCTION()
	void OnShipChoosen(int32 id);

	int32 CurrentPlayerIndex;
	EFFPhase ChoosePhase;

	TArray<int32> PlayersOrder;

	TArray<TSubclassOf<AFFActor>> LeaderCards;
	TArray<TSubclassOf<AFFActor>> Ships;

	UPROPERTY()
	AFFGameSequence_ChooseInList* ChooseInList;
};



