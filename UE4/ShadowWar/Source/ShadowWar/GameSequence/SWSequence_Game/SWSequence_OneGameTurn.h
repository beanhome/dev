// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence_OneGameTurn_Base.h"
#include "SWSequence_OneGameTurn.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_OneGameTurn : public AGSSequence_OneGameTurn_Base
{
	GENERATED_BODY()
public:
	struct FInit : public AGSSequence_OneGameTurn_Base::FInit
	{
		FInit(int32 _PlayerCount) : AGSSequence_OneGameTurn_Base::FInit(_PlayerCount) {}
	};

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	FSWPlayer& GetPlayingPlayer();
	const FSWPlayer& GetMyPlayer() const;

	/*
	virtual void BeginPlayerTurn();
	virtual void EndPlayerTurn();

protected:
	UFUNCTION()
	void OnPlayerTurnFinish(AGSSequence* Seq);
	*/

};
