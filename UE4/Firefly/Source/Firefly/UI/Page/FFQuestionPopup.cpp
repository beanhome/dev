// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "FFQuestionPopup.h"

#include "Game/FireflyPlayerController.h"


void UFFQuestionPopup::SetTitle(const FString& title)
{
	Title = title;
}

void UFFQuestionPopup::SetDesc(const FString& desc)
{
	Desc = desc;
}

void UFFQuestionPopup::SetOptions(const TArray<FFFOption>& options)
{
	Options = options;
	BPSetOptions(options);
}

void UFFQuestionPopup::AddOption(const FString& option)
{
	Options.Add(FFFOption(option, true));
}


void UFFQuestionPopup::OnButton_Select(int32 id)
{
	SelectAnswerDelegate.Broadcast(id);
}



