// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_SubTurn.generated.h"


UCLASS(minimalapi)
class AFFGameSequence_SubTurn : public AFFGameSequence
{
	GENERATED_BODY()

public:
	AFFGameSequence_SubTurn();
	
	class AFFGameSequence_Game* GetGame() const;
	class UFFGameHud* GetHud() const;

	const FFFPlayer& GetPlayer(int32) const;
	const FFFPlayer& GetPlayingPlayer() const;

	bool IsTurnOf(int32 id) const;
	bool IsMyTurn() const;

private:

};



