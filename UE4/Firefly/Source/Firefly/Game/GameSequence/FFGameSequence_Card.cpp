// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "Cards/FFCard.h"
#include "FFGameSequence_Card.h"
#include "FFGameSequence_GameTurns.h"
#include "Game/FireflyPlayerController.h"

AFFGameSequence_Card::AFFGameSequence_Card()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentChoice = -1;
	CurrentSequence = -1;
}

UTexture* AFFGameSequence_Card::GetFrontTexture()
{
	return FrontTexture;
}

void AFFGameSequence_Card::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*
	DOREPLIFETIME(AFFGameSequence_Card, State);
	DOREPLIFETIME(AFFGameSequence_Card, MoveStep);
	*/
}

bool AFFGameSequence_Card::IsCameraFree() const
{
	if (State == EFFClientGameSeqState::Ended)
		return true;

	return (CardState == EFFGSCardState::Fold || IsMyTurn() == false);
}

AFFCard* AFFGameSequence_Card::SpawnCardActor(UWorld* World)
{
	AFFCard* _Card = World->SpawnActor<AFFCard>(CardTemplate);
	_Card->FrontTexture = FrontTexture;
	_Card->BackTexture = BackTexture;
	_Card->CreateMaterialInstance();

	return _Card;
}

void AFFGameSequence_Card::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_Card::ServerStart()
{
	Super::ServerStart();

}

void AFFGameSequence_Card::Start()
{
	Super::Start();
	
	if (IsClient())
	{
		Card = SpawnCardActor(GetWorld());

		if (IsMyTurn())
		{
			Card->AttachToActor(GetFFPlayerController()->GetViewTarget(), FAttachmentTransformRules::KeepWorldTransform);

			Card->SetActorRelativeLocation(FVector::ForwardVector * 400.f);
			Card->SetActorRelativeRotation(FRotator(0.f, 90.f, 90.f));

			//GetFFPlayerController()->JumpToCamera(GetPlayer(GetMyPlayerId()).ShipBoard->Camera);

			CardState = EFFGSCardState::Interact;

			UStaticMeshComponent* CardComp = Card->FindComponentByClass<UStaticMeshComponent>();
			if (CardComp)
			{
				for (int32 i = 0; i < Choices.Num(); ++i)
				{
					Choices[i].Selector = CardComp->GetChildComponent(i);
				}
			}
		}
		else
		{
			Card->AttachToActor(GetPlayingPlayer().ShipBoard, FAttachmentTransformRules::KeepWorldTransform);

			Card->SetActorRelativeLocation(FVector(-100.f, 0.f, 50.f));
			Card->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
		}
	}
}

void AFFGameSequence_Card::End()
{
	Super::End();

	if (Card != nullptr)
		Card->Destroy();
}

bool AFFGameSequence_Card::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	if (IsTurnOf(PlayerId) == false)
		return false;

	switch (CardState)
	{
		case EFFGSCardState::Interact:
			if (Actor != Card)
			{
				if (IsClient())
					Card->SetActorRelativeLocation(FVector::ForwardVector * 400.f - FVector::RightVector * 400.f);
				CardState = EFFGSCardState::Fold;
			}
			else
			{
				if (IsClient())
				{
					UActorComponent* HoverComponent = GetFFPlayerController()->GetHoverComponent();
					int32 id = Choices.IndexOfByPredicate([&](const FFFGSCardChoice& elem) { return (elem.Selector == HoverComponent); });
					SendResponseToServer(id);
				}
				CardState = EFFGSCardState::Execute;
			}
			break;

		case EFFGSCardState::Fold:
			if (Actor == Card)
			{
				if (IsClient() && IsMyTurn())
					Card->SetActorRelativeLocation(FVector::ForwardVector * 400.f);
				CardState = EFFGSCardState::Interact;
			}
			break;
	}

	return true;
}

bool AFFGameSequence_Card::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}

bool AFFGameSequence_Card::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}


void AFFGameSequence_Card::OnSelectorClicked(AActor* TouchedActor, FKey ButtonPressed)
{

}


/*
void AFFGameSequence_Card::OnCardConfirmationAnswer(int32 id)
{
	check(IsClient());

	SendResponseToServer(id);
}
*/

void AFFGameSequence_Card::ServerReceiveResponse(int32 res)
{
	check(IsServer());

	AFFGameSequence* Effect = nullptr;

	switch (CardState)
	{
		case EFFGSCardState::Interact:
			check(res >= 0 && res < Choices.Num());
			CurrentChoice = res;
			CurrentSequence = 0;
			Effect = StartSubSequence(Choices[CurrentChoice].Sequences[CurrentSequence]);
			Effect->EndDelegate.AddDynamic(this, &AFFGameSequence_Card::CurrentEffectFinish);
			CardState = EFFGSCardState::Execute;
			break;

		case EFFGSCardState::Fold:
			break;

		case EFFGSCardState::Execute:
			break;

		default:
			break;
	}
}

void AFFGameSequence_Card::CurrentEffectFinish(AFFGameSequence* Seq)
{
	CurrentSequence++;

	if (CurrentSequence < Choices[CurrentChoice].Sequences.Num())
	{
		AFFGameSequence* Effect = StartSubSequence(Choices[CurrentChoice].Sequences[CurrentSequence]);
		Effect->EndDelegate.AddDynamic(this, &AFFGameSequence_Card::CurrentEffectFinish);
	}
	else
	{
		ServerStopCurrentSequence();
	}
}

void AFFGameSequence_Card::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (IsClient() && IsMyTurn() && Card != nullptr)
	{
		UActorComponent* HoverComponent = PlayerController->GetHoverComponent();

		switch (State)
		{
			case EFFGSCardState::Interact:

				for (int32 i = 0; i < Choices.Num(); ++i)
				{
					if (Choices[i].Selector != nullptr)
						Choices[i].Selector->SetVisibility(HoverComponent == Choices[i].Selector);
				}
				break;

			case EFFGSCardState::Fold:
				for (int32 i = 0; i < Choices.Num(); ++i)
				{
					if (Choices[i].Selector != nullptr)
						Choices[i].Selector->SetVisibility(false);
				}
				break;

			case EFFGSCardState::Execute:
				break;
		}
	}
}


void AFFGameSequence_Card::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColorList::Grey);

	x += 5.f;

	//y += Canvas->DrawText(Font, FString::Printf(TEXT("State %s"), *EnumToString(EFFFlyState, State)), x, y);
	//y += Canvas->DrawText(Font, FString::Printf(TEXT("Move Step %d"), MoveStep), x, y);

	x -= 5.f;
}
