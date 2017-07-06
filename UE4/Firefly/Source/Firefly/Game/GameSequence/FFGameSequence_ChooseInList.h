// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_ChooseInList.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChooseInList, int32, id);

class UFFGameHud;

UCLASS(minimalapi)
class AFFGameSequence_ChooseInList : public AFFGameSequence
{
	GENERATED_BODY()

public:
	struct FInit
	{
		FInit(const TArray<TSubclassOf<AFFActor>>& _List) : ClassList(_List) {}
		TArray<TSubclassOf<AFFActor>> ClassList;
	};

	AFFGameSequence_ChooseInList();
	
	void InitWithParam(AFFGameSequence* OwnerSequence, const FInit& _Init);
	virtual void Init(AFFGameSequence* OwnerSequence) override;
	virtual void Start() override;
	virtual void End() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetClassList(const TArray<TSubclassOf<class AFFActor>>& List);

	const TArray<TSubclassOf<AFFActor>>& GetList() const;

	int32 GetListCount() const;

	void AddCard(AFFActor* Card);
	void RemCard(AFFActor* Card);
	AFFActor* RemCard(int32 id);

protected:
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor) override;

private:
	FVector GetItemLocation(int32 selected, int32 id) const;

	UFUNCTION()
	void OnRep_SetChooseList();

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFFActor>> ClassList;

	UPROPERTY(ReplicatedUsing = OnRep_SetChooseList)
	TArray<AFFActor*> ChooseList;

public:
	UPROPERTY()
	FChooseInList ChooseInListDelegate;

	UPROPERTY(EditAnywhere)
	float DeepZ;

	UPROPERTY(EditAnywhere)
	float OffsetZ;

	UPROPERTY(EditAnywhere)
	float OffsetX;

	UPROPERTY(EditAnywhere)
	float PowX;

	FVector ItemExtent;

	int32 SelectedItem;
	int32 PreviousItem;
	int32 DesiredItem;

	float Timer;
	
	UPROPERTY(EditAnywhere)
	float Delay;
};



