// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSequence/SWSequence_Game/SWSequence_OnePlayerTurn/SWSequence_SubTurn.h"
#include "SWSequence_PrepareMove.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_PrepareMove : public ASWSequence_SubTurn
{
	GENERATED_BODY()

	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;
	virtual void Suspend() override;
	virtual void Resume() override;

	virtual bool OnMouseEnterActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseClickActor(int32 PlayerId, class AGSActor* Actor);

	virtual void Tick(float DeltaSeconds) override;

protected:
	void RefreshHoverFighter();

protected:
	class ASWFighter* HoverFighter; // Only use for client
};
