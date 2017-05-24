// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence_Card.h"
#include "FFGameSequence_GameTurns.h"
#include "Game/FireflyPlayerController.h"

AFFGameSequence_Card::AFFGameSequence_Card()
{
	//PrimaryActorTick.bCanEverTick = true;
}


void AFFGameSequence_Card::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*
	DOREPLIFETIME(AFFGameSequence_Card, State);
	DOREPLIFETIME(AFFGameSequence_Card, MoveStep);
	*/
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
	
	Card = GetWorld()->SpawnActor<AFFCard>(CardTemplate);

	FVector PlayerLoc = GetPlayingPlayer().ShipBoard->GetActorLocation();
	FRotator PlayerRot = GetPlayingPlayer().ShipBoard->GetActorRotation();

	Card->SetLocation(PlayerLoc + FVector::UpVector * 200.f);
	Card->SetRotation(PlayerRot);
}

void AFFGameSequence_Card::End()
{
	Super::End();
}

bool AFFGameSequence_Card::OnMouseClickActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}

bool AFFGameSequence_Card::OnMouseEnterActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}

bool AFFGameSequence_Card::OnMouseLeaveActor(int32 PlayerId, AFFActor* Actor)
{
	return false;
}


void AFFGameSequence_Card::OnCardConfirmationAnswer(int32 id)
{
	check(IsClient());

	SendResponseToServer(id);
}

void AFFGameSequence_Card::ServerReceiveResponse(int32 res)
{
	check(IsServer());
}


void AFFGameSequence_Card::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
