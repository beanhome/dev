// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Game/GameSequence/FFGameSequence.h"

#include "FFGameSequence_Question.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestion, int32, id);

class UFFGameHud;

UCLASS(minimalapi)
class AFFGameSequence_Question : public AFFGameSequence
{
	GENERATED_BODY()

public:
	struct FInit
	{
		FInit(const FString& _Title, const FString& _Desc, const TArray<FString>& _Answers) : Title(_Title), Desc(_Desc), Answers(_Answers) {}
		FString Title;
		FString Desc;
		TArray<FString> Answers;
	};

	AFFGameSequence_Question();

	virtual bool IsCameraFree() const override;
	virtual bool IsActorInteractive() const override;

	void InitWithParam(AFFGameSequence* OwnerSequence, const FInit& _Init);
	virtual void Start() override;
	virtual void End() override;

	UFUNCTION()
	void OnSelectAnswer(int32 id);

private:
	FString Title;
	FString Desc;
	TArray<FString> Answers;

public:
	UPROPERTY()
	FQuestion QuestionDelegate;

	UPROPERTY()
	class UFFQuestionPopup* Popup;
};



