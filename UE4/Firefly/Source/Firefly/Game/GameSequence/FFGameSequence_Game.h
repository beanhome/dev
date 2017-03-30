// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_Game.generated.h"

class UFFFreeAction;
class UFFGameHud;

UCLASS(minimalapi)
class AFFGameSequence_Game : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_Game();
	
	virtual void Init(AFFGameSequence* OwnerSequence) override;

	virtual void Start() override;
	virtual void End() override;

	UFFGameHud* GetGameHud();

	const TArray<int32>& GetPlayersOrder() const;

private:
	void ShufflePlayerOrder();

	UFUNCTION()
	void ChooseLeaderAndShipFinish(AFFGameSequence* Seq);

	UFUNCTION()
	void PlaceShipFinish(AFFGameSequence* Seq);

protected:
	TArray<int32> PlayersOrder;

	int32 CurrentPlayerIndex;

	UPROPERTY()
	UFFGameHud* GameHUD;
};



