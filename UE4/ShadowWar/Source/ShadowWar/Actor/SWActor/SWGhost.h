// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actor/SWActor.h"
#include "SWGhost.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWGhost : public ASWActor
{
	GENERATED_BODY()

public:

	ASWGhost();

	const class ASWFighter* GetFighter() const;
	class ASWFighter* GetFighter();
	void SetFighter(class ASWFighter* NewFighter);


public:
	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(Replicated)
	class ASWFighter* Fighter;
};
