// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Question.h"
#include "FFGameSequence_Game.h"
#include "Game/FFUITuning.h"
#include "UI/Page/FFQuestionPopup.h"

AFFGameSequence_Question::AFFGameSequence_Question()
{
}

void AFFGameSequence_Question::InitWithParam(AFFGameSequence* OwnerSequence, const FInit& Init)
{
	Title = Init.Title;
	Desc = Init.Desc;
	Answers = Init.Answers;

	Super::Init(OwnerSequence);
}

bool AFFGameSequence_Question::IsCameraFree() const
{
	return false;
}

bool AFFGameSequence_Question::IsActorInteractive() const
{
	return false;
}


void AFFGameSequence_Question::Start()
{
	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	Super::Start();

	const UFFUITuning* UITuning = GetDefaultUITuning();
	if (PlayerController && UITuning->QuestionPopupClass.GetDefaultObject())
	{
		Popup = CreateWidget<UFFQuestionPopup>(PlayerController, UITuning->QuestionPopupClass);
		Popup->AddToViewport();
		Popup->SetTitle(Title);
		Popup->SetDesc(Desc);
		Popup->SetOptions(Answers);
		Popup->SetVisibility(ESlateVisibility::Visible);

		Popup->SelectAnswerDelegate.AddDynamic(this, &AFFGameSequence_Question::OnSelectAnswer);
	}
}

void AFFGameSequence_Question::End()
{
	Super::End();

	if (Popup)
	{
		Popup->RemoveFromParent();
		Popup = nullptr;
	}
}

void AFFGameSequence_Question::OnSelectAnswer(int32 id)
{
	QuestionDelegate.Broadcast(id);
}
