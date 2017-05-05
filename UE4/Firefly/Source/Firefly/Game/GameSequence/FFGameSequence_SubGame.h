// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_SubGame.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_SubGame : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_SubGame();
	
	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	const class AFFGameSequence_Game* GetGame() const;
	class AFFGameSequence_Game* GetGame();

	class UFFGameHud* GetHud();

private:

};



