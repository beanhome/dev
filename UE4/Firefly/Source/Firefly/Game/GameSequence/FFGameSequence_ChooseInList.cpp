// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_ChooseInList.h"
#include "FFGameSequence_Game.h"

AFFGameSequence_ChooseInList::AFFGameSequence_ChooseInList()
: DeepZ(500.f)
, Delay(0.3f)
{
	PrimaryActorTick.bCanEverTick = true;
}

const TArray<TSubclassOf<AFFActor>>& AFFGameSequence_ChooseInList::GetList() const
{
	return List;
}

void AFFGameSequence_ChooseInList::Init(AFFGameSequence* OwnerSequence, const FInit& Init)
{
	List = Init.List;
	Super::Init(OwnerSequence);
}


void AFFGameSequence_ChooseInList::Start()
{
	Super::Start();

	ChooseList.SetNum(List.Num());

	for (int32 i = 0; i < List.Num(); ++i)
	{
		const TSubclassOf<AFFActor>& Actor = List[i];
		ChooseList[i] = GetWorld()->SpawnActor<AFFActor>(Actor);
		ChooseList[i]->ActorMouseClickDelegate.AddDynamic(this, &AFFGameSequence_ChooseInList::OnActorMouseClick);
		ChooseList[i]->ActorMouseEnterDelegate.AddDynamic(this, &AFFGameSequence_ChooseInList::OnActorMouseEnter);
	}

	if (ChooseList.Num() > 0)
		ItemExtent = ChooseList[0]->GetExtent();

	DesiredItem = SelectedItem = ChooseList.Num() / 2;
}

void AFFGameSequence_ChooseInList::End()
{
	Super::End();

	for (AFFActor* Actor : ChooseList)
		Actor->Destroy();
}

void AFFGameSequence_ChooseInList::OnActorMouseClick(AFFActor* ActorClicked)
{
	int32 id = ChooseList.Find(ActorClicked);

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
}

void AFFGameSequence_ChooseInList::OnActorMouseEnter(AFFActor* ActorEntered)
{
	int32 id = ChooseList.Find(ActorEntered);

	if (/*Timer <= 0.f &&*/ id != DesiredItem)
	{
		DesiredItem = id;
		
		if (Timer <= 0.f)
		{
			PreviousItem = SelectedItem;
			SelectedItem += FMath::Sign(DesiredItem - SelectedItem);
			Timer = Delay;
		}
	}
}

void AFFGameSequence_ChooseInList::Tick(float DeltaSecond)
{
	if (ChooseList.Num() == 0)
		return;

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

	return FVector(s * ItemExtent.X *0.5f * FMath::Pow(absdiff, 0.75f), 0.f, -DeepZ - absdiff * 30.f);
}

