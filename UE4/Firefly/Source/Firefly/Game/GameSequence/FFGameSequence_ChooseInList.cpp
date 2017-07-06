// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_ChooseInList.h"
#include "FFGameSequence_Game.h"
#include "FFGameSequence_Card.h"

AFFGameSequence_ChooseInList::AFFGameSequence_ChooseInList()
: DeepZ(500.f)
, OffsetZ(30.f)
, Delay(0.3f)
, PowX(0.75f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFFGameSequence_ChooseInList::SetClassList(const TArray<TSubclassOf<class AFFActor>>& List)
{
	ClassList = List;
}

const TArray<TSubclassOf<AFFActor>>& AFFGameSequence_ChooseInList::GetList() const
{
	return ClassList;
}

int32 AFFGameSequence_ChooseInList::GetListCount() const
{
	return ChooseList.Num();
}


void AFFGameSequence_ChooseInList::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_ChooseInList, ChooseList);
}


void AFFGameSequence_ChooseInList::OnRep_SetChooseList()
{
	if (ChooseList.Num() > 0 && ChooseList[0] != nullptr)
		ItemExtent = ChooseList[0]->GetExtent();
}



void AFFGameSequence_ChooseInList::InitWithParam(AFFGameSequence* OwnerSequence, const FInit& _Init)
{
	ClassList = _Init.ClassList;
	Init(OwnerSequence);
}

void AFFGameSequence_ChooseInList::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);

	if (IsServer() || IsLocal())
	{
		ChooseList.Empty();
		ChooseList.Reserve(ClassList.Num());

		for (const TSubclassOf<class AFFActor>& Actor : ClassList)
			ChooseList.Add(GetWorld()->SpawnActor<AFFActor>(Actor));
	}
}


void AFFGameSequence_ChooseInList::Start()
{
	Super::Start();

	if (ChooseList.Num() > 0)
		ItemExtent = ChooseList[0]->GetExtent();

	if (IsLocal() || IsClient())
	{
		PreviousItem = DesiredItem = SelectedItem = ChooseList.Num() / 2;
		Timer = Delay;
	}
}

void AFFGameSequence_ChooseInList::End()
{
	Super::End();

	if (IsLocal() || IsServer())
	{
		for (AFFActor* Actor : ChooseList)
			Actor->Destroy();
	}
}

void AFFGameSequence_ChooseInList::AddCard(AFFActor* Card)
{
	check(IsLocal() || IsServer());
	ChooseList.Insert(Card, SelectedItem);
}

void AFFGameSequence_ChooseInList::RemCard(AFFActor* Card)
{
	check(IsLocal() || IsServer());
	ChooseList.Remove(Card);
	SelectedItem = FMath::Clamp(SelectedItem, 0, ChooseList.Num()-1);
}

AFFActor* AFFGameSequence_ChooseInList::RemCard(int32 id)
{
	check(IsLocal() || IsServer());
	AFFActor* Card = ChooseList[id];
	RemCard(Card);
	return Card;
}


bool AFFGameSequence_ChooseInList::OnMouseClickActor(int32 PlayerId, AFFActor* ActorClicked)
{
	if (IsLocal() && PlayerId != GetMyPlayerId())
		return false;

	if (IsServer() && GetOwner<AFFGameSequence_SubTurn>()->IsTurnOf(PlayerId) == false)
		return false;

	int32 id = ChooseList.Find(ActorClicked);
	if (id == -1)
		return false;

	if (id == SelectedItem)
	{
		ChooseInListDelegate.Broadcast(id);
	}
	/*
	else
	{
		PreviousItem = SelectedItem;
		SelectedItem = id;
		Timer = Delay;
	}
	*/

	return true;
}

bool AFFGameSequence_ChooseInList::OnMouseEnterActor(int32 PlayerId, AFFActor* ActorEntered)
{
	if (IsLocal() && PlayerId != GetMyPlayerId())
		return false;

	if (IsServer() && GetOwner<AFFGameSequence_SubTurn>()->IsTurnOf(PlayerId) == false)
		return false;

	int32 id = ChooseList.Find(ActorEntered);
	if (id == -1)
		return false;

	if (/*Timer <= 0.f &&*/ id != DesiredItem)
	{
		DesiredItem = id;
		
		if (Timer <= 0.f || IsServer())
		{
			PreviousItem = SelectedItem;
			SelectedItem += FMath::Sign(DesiredItem - SelectedItem);
			Timer = Delay;
		}
	}

	return true;
}

bool AFFGameSequence_ChooseInList::OnMouseLeaveActor(int32 PlayerId, AFFActor* ActorEntered)
{
	if (IsLocal() && PlayerId != GetMyPlayerId())
		return false;

	if (IsServer() && GetOwner<AFFGameSequence_SubTurn>()->IsTurnOf(PlayerId) == false)
		return false;

	int32 id = ChooseList.Find(ActorEntered);
	return (id != -1);
}

void AFFGameSequence_ChooseInList::Tick(float DeltaSecond)
{
	if (ChooseList.Num() == 0)
		return;

	if (IsServer())
	{
		if (PreviousItem != SelectedItem)
		{
			PreviousItem = SelectedItem;
			if (SelectedItem != DesiredItem)
				SelectedItem += FMath::Sign(DesiredItem - SelectedItem);
		}
		return;
	}

	AFireflyPlayerController* Player = GetFFPlayerController();

	if (Timer > 0.f)
		Timer = FMath::Max(Timer - DeltaSecond, 0.f);
	
	float alpha = 1.f - Timer / Delay;

	for (int32 i = 0; i < ChooseList.Num(); ++i)
	{
		FVector loc;

		if (PreviousItem != SelectedItem)
			loc = FMath::Lerp(GetItemLocation(PreviousItem, i), GetItemLocation(SelectedItem, i), alpha);
		else
			loc = GetItemLocation(SelectedItem, i);
		
		FVector FrontAxis = Player->GetViewTarget()->GetTransform().GetUnitAxis(EAxis::X);
		FVector RightAxis = Player->GetViewTarget()->GetTransform().GetUnitAxis(EAxis::Y);
		FVector UpAxis = Player->GetViewTarget()->GetTransform().GetUnitAxis(EAxis::Z);
		FTransform CameraTransform(RightAxis, -UpAxis, -FrontAxis, Player->GetViewTarget()->GetActorLocation());

		loc = CameraTransform.TransformPosition(loc);
		FRotator rot = CameraTransform.Rotator();

		ChooseList[i]->SetLocation(loc);
		ChooseList[i]->SetRotation(rot);
	}

	if (Timer == 0.f && PreviousItem != SelectedItem)
	{
		PreviousItem = SelectedItem;
		if (SelectedItem != DesiredItem)
		{
			SelectedItem += FMath::Sign(DesiredItem - SelectedItem);
			Timer = Delay;
		}
	}
}

FVector AFFGameSequence_ChooseInList::GetItemLocation(int32 selected, int32 id) const
{
	float diff = (id - selected);
	float absdiff = FMath::Abs(diff);
	float s = FMath::Sign(diff);

	return FVector(OffsetX + s * ItemExtent.X *0.5f * FMath::Pow(absdiff, PowX), 0.f, -DeepZ - absdiff * OffsetZ);
}


