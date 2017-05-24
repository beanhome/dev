// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence_SubTurn.h"

#include "FFGameSequence_Card.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_Card : public AFFGameSequence_SubTurn
{
	GENERATED_BODY()

public:
	AFFGameSequence_Card();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

protected:
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

	UFUNCTION()
	void OnCardConfirmationAnswer(int32 id);

	virtual void ServerReceiveResponse(int32 res) override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFCard> CardTemplate;
	
	UPROPERTY()
	class AFFCard* Card;
};



