// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSequence/SWSequence_SubGame.h"
#include "SWSequence_SubTurn.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWSequence_SubTurn : public ASWSequence_SubGame
{
	GENERATED_BODY()

public:
	const FSWPlayer& GetPlayer(int32) const;
	FSWPlayer& GetPlayingPlayer() const;
	const FSWPlayer& GetMyPlayer() const;

	bool IsTurnOf(int32 id) const;
	bool IsMyTurn() const;

protected:

};
