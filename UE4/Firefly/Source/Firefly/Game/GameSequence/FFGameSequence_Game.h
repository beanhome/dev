// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_Game.generated.h"

USTRUCT()
struct FFFPlayer
{
	GENERATED_BODY()

	UPROPERTY()
	class AFFLeaderCard* Leader;
	
	UPROPERTY()
	class AFFShipBoard* ShipBoard;

	UPROPERTY()
	class AFFEngineCard* Engine;

	UPROPERTY()
	class AFFShip* Ship;
};

UCLASS(minimalapi)
class AFFGameSequence_Game : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_Game();

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	virtual void ServerInit(AFFGameSequence* OwnerSequence) override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;

	virtual void Start() override;
	virtual void End() override;

	class UFFGameHud* GetGameHud();

	virtual bool IsCameraFree() const override;

	const FFFPlayer& GetPlayer(int32 Id) const;

	const TArray<int32>& GetPlayersOrder() const;

	void PlayerChooseLeader(int32 PlayerId, TSubclassOf<class AFFActor>& LeaderCard);
	void PlayerChooseShip(int32 PlayerId, TSubclassOf<class AFFActor>& ShipCard);
	void PlayerPlaceShip(int32 PlayerId, int32 SectorId);

	TSubclassOf<class AFFGameSequence_Card> DrawNavigationCard();

private:
	void ShufflePlayerOrder();

	UFUNCTION()
	void ChooseLeaderAndShipFinish(AFFGameSequence* Seq);

	UFUNCTION()
	void PlaceShipFinish(AFFGameSequence* Seq);

	UFUNCTION()
	void GameOver(AFFGameSequence* Seq);

public:
	UFUNCTION(Reliable, NetMulticast)
	void ReceiveMouseEnterActor(int32 PlayerId, class AFFActor* Actor);

	UFUNCTION(Reliable, NetMulticast)
	void ReceiveMouseLeaveActor(int32 PlayerId, class AFFActor* Actor);

	UFUNCTION(Reliable, NetMulticast)
	void ReceiveMouseClickActor(int32 PlayerId, class AFFActor* Actor);

protected:
	TArray<int32> PlayersOrder;

	UPROPERTY()
	class UFFGameHud* GameHUD;

	UPROPERTY(Replicated)
	TArray<FFFPlayer> Players;

	//UPROPERTY()
	//class AFFDeck* NavigationAllianceDeck;
};



