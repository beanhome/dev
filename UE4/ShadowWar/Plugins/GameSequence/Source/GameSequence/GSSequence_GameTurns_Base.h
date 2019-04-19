// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence.h"
#include "GSSequence_GameTurns_Base.generated.h"

/**
 * 
 */
UCLASS()
class GAMESEQUENCE_API AGSSequence_GameTurns_Base : public AGSSequence
{
	GENERATED_BODY()

public:
	AGSSequence_GameTurns_Base();

	struct FInit : public FGSSequenceInit
	{
		FInit(int32 _MaximumTurnCount = -1) : MaximumTurnCount(_MaximumTurnCount) {}
		FInit(const TSubclassOf<class AGSSequence>& _GameTurnSequence) : MaximumTurnCount(-1), OneGameTurnSequence(_GameTurnSequence) {}
		FInit(int32 _MaximumTurnCount, const TSubclassOf<class AGSSequence>& _GameTurnSequence) : MaximumTurnCount(_MaximumTurnCount), OneGameTurnSequence(_GameTurnSequence) {}
		FInit(const FInit& orig) : MaximumTurnCount(orig.MaximumTurnCount), OneGameTurnSequence(orig.OneGameTurnSequence) {}
		int32 MaximumTurnCount;
		TSubclassOf<class AGSSequence> OneGameTurnSequence;
	};

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const override;

protected:
	void StartGameTurn(int32 turn);
	void StopGameTurn();

private:
	UFUNCTION(Reliable, NetMulticast)
	void OnStartGameTurn(int32 turn);

	UFUNCTION(Reliable, NetMulticast)
	void OnStopGameTurn();

protected:
	virtual void BeginGameTurn();
	virtual void EndGameTurn();

protected:
	UFUNCTION()
	void OnGameTurnFinish(AGSSequence* Seq);

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 MaximumTurnCount;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGSSequence> OneGameTurnSequence;

	int32 CurrentTurn;

};
