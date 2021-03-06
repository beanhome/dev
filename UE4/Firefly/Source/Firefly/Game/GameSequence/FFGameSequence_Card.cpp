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

void AFFGameSequence_Card::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_Card, Card);
}

bool AFFGameSequence_Card::IsCameraFree() const
{
	if (State == EFFClientGameSeqState::Ended)
		return true;

	return (CardState == EFFGSCardState::Fold || IsMyTurn() == false);
}

void AFFGameSequence_Card::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

const AFFNavCard* AFFGameSequence_Card::GetCard() const
{
	return Card;
}

void AFFGameSequence_Card::SetCard(AFFNavCard* _Card)
{
	Card = _Card;
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
		check(Card);

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
				for (int32 i = 0; i < Card->Choices.Num(); ++i)
				{
					Card->Choices[i].Selector = CardComp->GetChildComponent(i);
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
				Fold();
			}
			else
			{
				if (IsClient())
				{
					UActorComponent* HoverComponent = GetFFPlayerController()->GetHoverComponent();
					int32 id = Card->Choices.IndexOfByPredicate([&](const FFFGSCardChoice& elem) { return (elem.Selector == HoverComponent); });
					if (id != -1)
					{
						if (IsChoiceValidFor(Card->Choices[id], GetPlayer(PlayerId)))
						{
							SendResponseToServer(id);
							CardState = EFFGSCardState::Execute;
						}
						else
						{
							// Show Message
						}
					}
				}
			}
			break;

		case EFFGSCardState::Fold:
			if (Actor == Card)
				UnFold();
			break;
	}

	return true;
}

void AFFGameSequence_Card::Fold()
{
	if (IsClient() && IsMyTurn())
		Card->SetActorRelativeLocation(FVector::ForwardVector * 400.f - FVector::RightVector * 400.f);
	CardState = EFFGSCardState::Fold;
}

void AFFGameSequence_Card::UnFold()
{
	if (IsClient() && IsMyTurn())
		Card->SetActorRelativeLocation(FVector::ForwardVector * 400.f);
	CardState = EFFGSCardState::Interact;
}


bool AFFGameSequence_Card::IsChoiceValidFor(const FFFGSCardChoice& Choise, const FFFPlayer& Player) const
{
	for (const TSubclassOf<class AFFGameSequence_Effect>& Effect : Choise.Sequences)
	{
		if (Effect.GetDefaultObject() && Effect.GetDefaultObject()->IsValidFor(Player) == false)
			return false;
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
			check(res >= 0 && res < Card->Choices.Num());
			CurrentChoice = res;
			if (StartNextEffect())
				CardState = EFFGSCardState::Execute;
			else
				ServerStopCurrentSequence();
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
	if (StartNextEffect() == false)
	{
		ServerStopCurrentSequence();
	}
}

bool AFFGameSequence_Card::StartNextEffect()
{
	TSubclassOf<class AFFGameSequence_Effect> SeqClass;

	while (++CurrentSequence < Card->Choices[CurrentChoice].Sequences.Num())
	{
		SeqClass = Card->Choices[CurrentChoice].Sequences[CurrentSequence];

		if (SeqClass)
			break;
	}

	if (SeqClass)
	{
		AFFGameSequence* Effect = StartSubSequence(SeqClass);
		Effect->EndDelegate.AddDynamic(this, &AFFGameSequence_Card::CurrentEffectFinish);
	}

	return SeqClass != nullptr;
}


void AFFGameSequence_Card::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AFireflyPlayerController* PlayerController = GetFFPlayerController();

	if (IsClient() && IsMyTurn() && Card != nullptr)
	{
		UActorComponent* HoverComponent = PlayerController->GetHoverComponent();

		switch (CardState)
		{
			case EFFGSCardState::Interact:

				for (int32 i = 0; i < Card->Choices.Num(); ++i)
				{
					if (Card->Choices[i].Selector != nullptr)
						Card->Choices[i].Selector->SetVisibility(HoverComponent == Card->Choices[i].Selector);
				}
				break;

			case EFFGSCardState::Fold:
				for (int32 i = 0; i < Card->Choices.Num(); ++i)
				{
					if (Card->Choices[i].Selector != nullptr)
						Card->Choices[i].Selector->SetVisibility(false);
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
