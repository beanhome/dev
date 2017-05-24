// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Fly.h"
#include "FFGameSequence_GameTurns.h"
#include "FFGameSequence_Question.h"
#include "Game/FireflyPlayerController.h"
#include "Board/FFSector.h"
#include "Game/FFPathFinder.h"
#include "Cards/Cards/FFEngineCard.h"

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

	MoveStep = Engine->GetMoveCount();

	PathFinder = NewObject<UFFPathFinder>(this);

	ShowZone();
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
					FString Title = "Start Flying ?";
					FString Desc = "Initiate full burn or mosey";
					TArray<FString> Options;
					for (char* option : s_sOptions)
						Options.Add(option);

					Confirmation = StartLocalSubSequence<AFFGameSequence_Question>(AFFGameSequence_Question::StaticClass(), AFFGameSequence_Question::FInit(Title, Desc, Options));
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

	// Consume one fuel
	// ...
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
			// Notify action count
			// ...
			if (IsServer())
				ServerStopCurrentSequence();
			break;

		case EFFFlyState::FullBurn:
			Zone.Empty();

			if (IsServer())
			{
				DrawNavigationCard();

			}

			if (MoveStep > 0)
			{
				if (IsClient() && IsMyTurn())
				{
					ShowZone();
					ShowPaths(Hover);
					Hover->HighLight(true);
				}
			}
			else
			{
				// Notify action count
				// ...

				if (IsServer())
					ServerStopCurrentSequence();
			}

			break;
	}
}

void AFFGameSequence_Fly::DrawNavigationCard()
{
	if (ShipSector->GetDeck())
	{
		TSubclassOf<class AFFGameSequence_Card> DrawnCard = ShipSector->GetDeck()->DrawCard();

		AFFGameSequence_Card* DrawCardSequence = StartSubSequence<AFFGameSequence_Card>(DrawnCard);
		DrawCardSequence->EndDelegate.AddDynamic(this, &AFFGameSequence_Fly::OnDrawNavigationCardFinished);
	}
}

void AFFGameSequence_Fly::OnDrawNavigationCardFinished(AFFGameSequence * Seq)
{

}


void AFFGameSequence_Fly::DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const
{
	UFont* Font = GEngine->GetSmallFont();
	Canvas->SetDrawColor(FColorList::Grey);

	x += 5.f;

	y += Canvas->DrawText(Font, FString::Printf(TEXT("State %s"), *EnumToString(EFFFlyState, State)), x, y);
	y += Canvas->DrawText(Font, FString::Printf(TEXT("Move Step %d"), MoveStep), x, y);

	x -= 5.f;
}
