// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_Fly.generated.h"

class UFFFreeAction;
class AFFCameraActor;

UCLASS(minimalapi)
class AFFGameSequence_Fly : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_Fly();

	virtual bool IsCameraFree() const;

private:
	virtual void ServerStart() override;

	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

protected:
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

private:

	UPROPERTY()
	class UFFPathFinder* PathFinder;

	FFFPath Path;
};



