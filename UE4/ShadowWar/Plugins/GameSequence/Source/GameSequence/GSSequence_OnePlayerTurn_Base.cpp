// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSequence.h"
#include "GSSequence_OnePlayerTurn_Base.h"
#include "GSSequence_OneGameTurn_Base.h"

bool AGSSequence_OnePlayerTurn_Base::IsTurnOf(int32 id) const
{
	return GetOwner<AGSSequence_OneGameTurn_Base>()->IsTurnOf(id);
}

bool AGSSequence_OnePlayerTurn_Base::IsMyTurn() const
{
	return GetOwner<AGSSequence_OneGameTurn_Base>()->IsMyTurn();
}

void AGSSequence_OnePlayerTurn_Base::Init(AGSSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);

	check(GetOwner<AGSSequence_OneGameTurn_Base>() != nullptr);
}

void AGSSequence_OnePlayerTurn_Base::Start()
{
	Super::Start();
}

void AGSSequence_OnePlayerTurn_Base::End()
{
	Super::End();
}

