// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence.h"
#include "GSSequence_OneGameTurn_Base.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEQUENCE_API AGSSequence_OneGameTurn_Base : public AGSSequence
{
	GENERATED_BODY()

public:
	AGSSequence_OneGameTurn_Base();

	struct FInit : public FGSSequenceInit
	{
		FInit(int32 _PlayerCount) : PlayerCount(_PlayerCount) {}
		FInit(const TArray<int32>& _PlayersOrder) : PlayerCount(0), PlayersOrder(_PlayersOrder) {}
		FInit(int32 _PlayerCount, const TSubclassOf<class AGSSequence_OnePlayerTurn_Base>& _PlayerTurnSequence) : PlayerCount(_PlayerCount), OnePlayerTurnSequence(_PlayerTurnSequence) {}
		FInit(const TArray<int32>& _PlayersOrder, const TSubclassOf<class AGSSequence_OnePlayerTurn_Base>& _PlayerTurnSequence) : PlayerCount(0), PlayersOrder(_PlayersOrder), OnePlayerTurnSequence(_PlayerTurnSequence) {}
		FInit(const FInit& orig) : PlayerCount(orig.PlayerCount), PlayersOrder(orig.PlayersOrder), OnePlayerTurnSequence(orig.OnePlayerTurnSequence) {}
		int32 PlayerCount;
		TArray<int32> PlayersOrder;
		TSubclassOf<class AGSSequence_OnePlayerTurn_Base> OnePlayerTurnSequence;
	};

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const override;

	bool IsTurnOf(int32 id) const;
	bool IsMyTurn() const;

protected:
	void StartPlayerTurn(int32 id);
	void StopPlayerTurn();

private:
	UFUNCTION(Reliable, NetMulticast)
	void OnStartPlayerTurn(int32 id);

	UFUNCTION(Reliable, NetMulticast)
	void OnStopPlayerTurn();

protected:
	virtual void BeginPlayerTurn();
	virtual void EndPlayerTurn();

private:
	UFUNCTION()
	void OnPlayerTurnFinish(AGSSequence* Seq);

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 PlayerCount;

	UPROPERTY(EditDefaultsOnly)
	TArray<int32> PlayersOrder;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGSSequence_OnePlayerTurn_Base> OnePlayerTurnSequence;

	int32 CurrentPlayerIndex;
	int32 CurrentPlayerId;
};
