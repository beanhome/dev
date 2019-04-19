// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence_OnePlayerTurn_Base.h"
#include "SWSequence_Setup.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_Setup : public AGSSequence_OnePlayerTurn_Base
{
	GENERATED_BODY()

public:
	virtual void Start() override;
	virtual void End() override;

	virtual void ServerReceiveResponse(FGSResponse res) override;

	virtual bool OnMouseClickActor(int32 PlayerId, class AGSActor* Actor);

	UFUNCTION()
	void OnClickEndTurn();

protected:
	void OnEndPlaceSequences(AGSSequence* Ses);
};
