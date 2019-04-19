// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Fly.h"
#include "FFGameSequence_GameTurns.h"
#include "FFGameSequence_Question.h"
#include "FFGameSequence_Shuffle.h"
#include "FFGameSequence_Card.h"
#include "Game/FireflyPlayerController.h"
#include "Board/FFSector.h"
#include "Board/FFShipBoard.h"
#include "Game/FFPathFinder.h"
#include "Cards/Cards/FFEngineCard.h"
#include "UI/Page/FFSpecificHud.h"

char* AFFGameSequence_Fly::s_sOptions[] =
{
	"Mosey",
	"FullBurn",
	"Cancel"
};

AFFGameSequence_Fly::AFFGameSequence_Fly()
	: PathFinder(nullptr)
{
	m_fDelay = 1.f;
	PrimaryActorTick.bCanEverTick = true;
}


void AFFGameSequence_Fly::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFFGameSequence_Fly, State);
	DOREPLIFETIME(AFFGameSequence_Fly, MoveStep);
}

void AFFGameSequence_Fly::Init(AFFGameSequence* OwnerSequence)
{
	Super::Init(OwnerSequence);
}

void AFFGameSequence_Fly::ServerStart()
{
	Super::ServerStart();

}

void AFFGameSequence_Fly::Start()
{
	Super::Start();

	const FFFPlayer& Player = GetPlayingPlayer();
	Ship = Player.Ship;
	ShipSector = Ship->GetCurrentSector();
	Engine = Player.ShipBoard->GetEngine();

	bool bHasFuel = Player.ShipBoard->HasStuff(FuelBlueprint);

	MoveStep = (bHasFuel ? Engine->GetMoveCount() : 1);

	PathFinder = NewObject<UFFPathFinder>(this);

	ShowZone();

	if (SpecificHud)
		SpecificHud->SetVisibility(ESlateVisibility::Hidden);
}

void AFFGameSequence_Fly::End()
{
	Super::End();

	HideZone();

	PathFinder = nullptr;
}

bool AFFGameSequence_Fly::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	bool bCurrentPlayerTurn = IsTurnOf(PlayerId);

	if (!bCurrentPlayerTurn)
		return false;

	switch (State)
	{
		case EFFFlyState::Free:
			if (IsServer() && Zone.Contains(Sector) == false)
			{
				ServerStopCurrentSequence();
			}
			else if (ShipSector->GetLinks().Contains(Sector))
			{
				Destination = Sector;

				if (IsClient() && IsMyTurn())
				{
					AFFGameSequence_Question::FInit Init;
					Init.Title = "Start Flying ?";
					Init.Desc = "Initiate full burn or mosey";
					for (int32 i = 0; i < (int32)EFFFlyOptions::Count; ++i)
					{
						bool bEnable = true;

						if (i == (int32)EFFFlyOptions::FullBurn)
						{
							bEnable = GetPlayingPlayer().ShipBoard->HasStuff(FuelBlueprint);
						}

						Init.Options.Add(FFFOption(s_sOptions[i], bEnable));
					}

					Confirmation = StartLocalSubSequence<AFFGameSequence_Question>(AFFGameSequence_Question::StaticClass(), Init);
					Confirmation->QuestionDelegate.AddDynamic(this, &AFFGameSequence_Fly::OnFlyConfirmationAnswer);
				}
			}
			break;

		case EFFFlyState::FullBurn:
			if (Destination == nullptr && ShipSector->GetLinks().Contains(Sector))
			{
				Destination = Sector;
				StartFullBurn(Destination);
			}
	}

	return true;
}

bool AFFGameSequence_Fly::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	Hover = Sector;

	if (State == EFFFlyState::Free || (State == EFFFlyState::FullBurn && Destination == nullptr))
	{
		if (IsClient() && IsMyTurn() && Zone.Contains(Sector))
		{
			ShowPaths(Sector);
			Sector->HighLight(true);
		}
	}

	return true;
}

bool AFFGameSequence_Fly::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	AFFSector* Sector = Cast<AFFSector>(Actor);
	if (Sector == nullptr)
		return false;

	Hover = nullptr;

	if (State == EFFFlyState::Free || (State == EFFFlyState::FullBurn && Destination == nullptr))
	{
		HidePaths();
		Sector->HighLight(false);
	}

	return true;
}


void AFFGameSequence_Fly::OnFlyConfirmationAnswer(int32 id)
{
	check(IsClient());

	StopLocalSubSequence(Confirmation);

	SendResponseToServer(id);
}

void AFFGameSequence_Fly::ServerReceiveResponse(int32 res)
{
	check(IsServer());

	switch ((EFFFlyOptions)res)
	{
	case EFFFlyOptions::Mosey:
		StartMosey(Destination);
		break;

	case EFFFlyOptions::FullBurn:
		StartFullBurn(Destination);
		GetPlayingPlayer().ShipBoard->RemStuff(FuelBlueprint);
		break;

	default:
		Destination = nullptr;
		break;
	}
}


void AFFGameSequence_Fly::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (State)
	{
		case EFFFlyState::Free:
			break;

		case EFFFlyState::Mosey:
		case EFFFlyState::FullBurn:
			if (Destination != nullptr)
			{
				m_fTime += DeltaSeconds;

				float alpha = m_fTime / m_fDelay;
				alpha = FMath::Min(alpha, 1.f);

				FVector Start = ShipSector->GetCenter();
				FVector End = Destination->GetCenter();
				
				FVector loc = FMath::Lerp(Start, End, alpha);

				Ship->SetLocation(loc);

				if (m_fTime > m_fDelay)
				{
					ReachDestination();
				}
			}
			break;
	}
}

void AFFGameSequence_Fly::ShowZone()
{
	if (Zone.IsEmpty())
	{
		PathFinder->GetSectorsAtDist(ShipSector, MoveStep, Zone);
	}

	if (IsClient() && IsMyTurn())
	{
		for (const FFFPathNode& Node : Zone.Path)
		{
			Node.Sector->HighLight(true);
			//DrawDebugLine(GetWorld(), Node.Sector->GetCenter(), Node.Sector->GetCenter() + FVector::UpVector * 100.f, FColor::White, true);
			//DrawDebugString(GetWorld(), Node.Sector->GetCenter() + FVector(0.f, 0.f, 0.f), FString::Printf(TEXT("%d"), Node.PathCost), nullptr, FColor::White, -1.f);
		}
	}
}

void AFFGameSequence_Fly::HideZone()
{
	for (const FFFPathNode& Node : Zone.Path)
		Node.Sector->HighLight(false);
}

void AFFGameSequence_Fly::ShowPaths(AFFSector* Dest)
{
	Path.Empty();

	PathFinder->FindAllPath(ShipSector, Dest, MoveStep, Path);

	for (const FFFPathNode& Node : Path.Path)
		Node.Sector->HighLight(true);
}

void AFFGameSequence_Fly::HidePaths()
{
	for (const FFFPathNode& Node : Path.Path)
		Node.Sector->HighLight(false);

	Path.Empty();
}



void AFFGameSequence_Fly::StartMosey_Implementation(AFFSector* Dest)
{
	Destination = Dest;

	HidePaths();
	Dest->HighLight(false);
	HideZone();

	State = EFFFlyState::Mosey;
	m_fTime = 0.f;
}

void AFFGameSequence_Fly::StartFullBurn_Implementation(AFFSector* Dest)
{
	Destination = Dest;

	HidePaths();
	Dest->HighLight(false);
	HideZone();

	State = EFFFlyState::FullBurn;
	m_fTime = 0.f;

	MoveStep--;

	if (SpecificHud)
		SpecificHud->SetVisibility(ESlateVisibility::Hidden);
}

void AFFGameSequence_Fly::ReachDestination()
{
	Ship->SetLocation(Destination->GetCenter());
	Ship->SetSector(Destination);
	ShipSector = Destination;
	Destination = nullptr;

	switch (State)
	{
		case EFFFlyState::Free:
			break;

		case EFFFlyState::Mosey:
			if (IsServer())
			{
				ConsumeAction();
				ServerStopCurrentSequence();
			}
			break;

		case EFFFlyState::FullBurn:
			Zone.Empty();

			if (IsServer())
			{
				DrawNavigationCard();
			}

			break;
	}
}

void AFFGameSequence_Fly::DrawNavigationCard()
{
	check(IsServer());

	if (ShipSector->GetDeck())
	{
		class AFFCard* DrawnCard = ShipSector->GetDeck()->DrawCard().GetDefaultObject();

		if (DrawnCard == nullptr)
		{
			AFFGameSequence_Shuffle* ShuffleSequence = StartSubSequence<AFFGameSequence_Shuffle>();
			ShuffleSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Fly::OnShuffleDeckFinished);
			ShuffleSequence->SetDeck(ShipSector->GetDeck());
		}
		else
		{
			AFFNavCard* DrawnNavCard = Cast<AFFNavCard>(DrawnCard);

			ensure(DrawnNavCard != nullptr);

			if (DrawnNavCard != nullptr)
			{
				AFFGameSequence_Card* DrawCardSequence = StartSubSequence<AFFGameSequence_Card>(DrawnNavCard->GetSequenceTemplate());
				AFFNavCard* ShowNavCard = GetWorld()->SpawnActor<AFFNavCard>(DrawnNavCard->GetClass());
				DrawCardSequence->SetCard(ShowNavCard);
				DrawCardSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Fly::OnDrawNavigationCardFinished);
			}
		}
	}
}

void AFFGameSequence_Fly::OnShuffleDeckFinished(AFFGameSequence * Seq)
{
	check(IsServer());

	DrawNavigationCard();
}

void AFFGameSequence_Fly::OnDrawNavigationCardFinished(AFFGameSequence * Seq)
{
	check(IsServer());

	AFFGameSequence_Card* DrawCardSequence = Cast<AFFGameSequence_Card>(Seq);

	ShipSector->GetDeck()->Discard(DrawCardSequence->GetCard()->GetClass());

	if (MoveStep > 0)
	{
		FinishMove();
	}
	else
	{
		if (IsServer())
		{
			ConsumeAction();
			ServerStopCurrentSequence();
		}
	}

}

void AFFGameSequence_Fly::FinishMove_Implementation()
{
	if (IsClient() && IsMyTurn())
	{
		if (SpecificHud)
			SpecificHud->SetVisibility(ESlateVisibility::Visible);

		ShowZone();
		if (Hover)
		{
			ShowPaths(Hover);
			Hover->HighLight(true);
		}
	}
}


void AFFGameSequence_Fly::FullStop()
{
	check(IsServer());

	MoveStep = 0;
}

void AFFGameSequence_Fly::OnValidate()
{
	Super::OnValidate();

	if (IsServer())
		ServerStopCurrentSequence();
}

void AFFGameSequence_Fly::OnCancel()
{
	Super::OnCancel();

	if (IsServer())
		ServerStopCurrentSequence();
}


void AFFGameSequence_Fly::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColorList::Grey);

	y += Canvas->DrawText(Font, FString::Printf(TEXT("State %s"), *EnumToString(EFFFlyState, State)), x, y);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("Move Step %d"), MoveStep), x, y);
}
