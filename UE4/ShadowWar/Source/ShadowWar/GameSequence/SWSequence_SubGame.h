// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GSSequence.h"
#include "SWSequence_SubGame.generated.h"

UCLASS(minimalapi)
class ASWSequence_SubGame : public AGSSequence
{
	GENERATED_BODY()

public:
	ASWSequence_SubGame();
	
	virtual void Init(AGSSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	const class ASWSequence_Game* GetGame() const;
	class ASWSequence_Game* GetGame();

	class USWGameHud* GetHud();

private:

};



