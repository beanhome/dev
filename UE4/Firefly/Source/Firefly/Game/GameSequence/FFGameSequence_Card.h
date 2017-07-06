// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubTurn.h"
#include "Game/GameSequence/FFGameSequence_Effect.h"

#include "FFGameSequence_Card.generated.h"

UENUM()
enum class EFFGSCardState : uint8
{
	Interact,
	Fold,
	Execute,
};

UCLASS(minimalapi)
class AFFGameSequence_Card : public AFFGameSequence_SubTurn
{
	GENERATED_BODY()

public:
	AFFGameSequence_Card();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	const AFFNavCard* GetCard() const;
	void SetCard(AFFNavCard* _Card);

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual bool IsCameraFree() const;

protected:
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

	UFUNCTION()
	void CurrentEffectFinish(AFFGameSequence* Seq);

	virtual void ServerReceiveResponse(int32 res) override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const override;

	UFUNCTION()
	void OnSelectorClicked(AActor* TouchedActor, FKey ButtonPressed);

private:
	UPROPERTY(Replicated)
	class AFFNavCard* Card;

	UPROPERTY()
	EFFGSCardState CardState;

	int32 CurrentChoice;
	int32 CurrentSequence;
};



