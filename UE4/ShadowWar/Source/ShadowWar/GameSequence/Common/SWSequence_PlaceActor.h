// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSSequence_OnePlayerTurn_Base.h"
#include "SWSequence_PlaceActor.generated.h"


/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_PlaceActor : public AGSSequence_OnePlayerTurn_Base
{
	GENERATED_BODY()

public:
	enum EPhase
	{
		Place,
		Rotate
	};

	struct FInit : public FGSSequenceInit
	{
		FInit(class ASWActor* _Actor) : Actor(_Actor) {}
		FInit(class ASWActor* _Actor, const TArray<class AActor*>& lst) : Actor(_Actor), LimitationActors(lst) {}
		FInit(class ASWActor* _Actor, class AActor* LimitActor) : Actor(_Actor) { LimitationActors.Add(LimitActor); }
		FInit(const FInit& orig) : Actor(orig.Actor), LimitationActors(orig.LimitationActors) {}
		class ASWActor* Actor;
		TArray<class AActor*> LimitationActors;
	};

public:
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual bool OnMouseEnterActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseClickActor(int32 PlayerId, class AGSActor* Actor);

	virtual void Tick(float DeltaSeconds) override;

	virtual void ServerReceiveResponse(FGSResponse res) override;


private:
	UFUNCTION()
	void OnRep_Actor(class ASWActor* _Actor);

protected:
	UPROPERTY(ReplicatedUsing=OnRep_Actor)
	class ASWActor* Actor;

	UPROPERTY(Replicated)
	TArray<class AActor*> LimitationActors;

	EPhase Phase;
};
