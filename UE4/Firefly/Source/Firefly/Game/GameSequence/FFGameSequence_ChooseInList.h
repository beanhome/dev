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
		FInit(const TArray<TSubclassOf<AFFActor>>& _List) : List(_List) {}
		TArray<TSubclassOf<AFFActor>> List;
	};

	AFFGameSequence_ChooseInList();
	
	void InitWithParam(AFFGameSequence* OwnerSequence, const FInit& _Init);
	virtual void Start() override;
	virtual void End() override;

	virtual void Tick(float DeltaSeconds) override;

	const TArray<TSubclassOf<AFFActor>>& GetList() const;

protected:
	virtual bool OnMouseEnterActor(class AFFActor* Actor) override;
	virtual bool OnMouseExitActor(class AFFActor* Actor) override;
	virtual bool OnMouseClickActor(class AFFActor* Actor) override;

private:
	FVector GetItemLocation(int32 selected, int32 id) const;

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFFActor>> List;

	UPROPERTY()
	TArray<AFFActor*> ChooseList;

public:
	UPROPERTY()
	FChooseInList ChooseInListDelegate;

	UPROPERTY(EditAnywhere)
	float DeepZ;

	FVector ItemExtent;

	int32 SelectedItem;
	int32 PreviousItem;
	int32 DesiredItem;

	float Timer;
	
	UPROPERTY(EditAnywhere)
	float Delay;
};



