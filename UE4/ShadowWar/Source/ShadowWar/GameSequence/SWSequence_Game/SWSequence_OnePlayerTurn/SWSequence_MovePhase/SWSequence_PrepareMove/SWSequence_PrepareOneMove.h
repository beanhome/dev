// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSequence/SWSequence_Game/SWSequence_OnePlayerTurn/SWSequence_SubTurn.h"
#include "SWSequence_PrepareOneMove.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_PrepareOneMove : public ASWSequence_SubTurn
{
	GENERATED_BODY()

	friend class ASWSequence_PrepareMove;

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual bool OnMouseEnterActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseClickActor(int32 PlayerId, class AGSActor* Actor);

	virtual void ServerReceiveResponse(FGSResponse res) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION()
	void OnEndPlaceSequences(AGSSequence* Seq);


protected:
	UPROPERTY(Replicated)
	class ASWFighter* Fighter;
};
