// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFPlayerInfo.h"
#include "FFPlayerPawn.h"
#include "FireflyPlayerController.h"
#include "Board/FFSector.h"
#include "Cards/Cards/FFEngineCard.h"
#include "FFGameTuning.h"

#include "Engine.h"

UFFPlayerInfo::UFFPlayerInfo()
{
}

int32 UFFPlayerInfo::GetId() const
{
	return Id;
}

void UFFPlayerInfo::SetId(int32 id)
{
	Id = id;
}

const AFireflyPlayerController* UFFPlayerInfo::GetController() const
{
	return Controller;
}

void UFFPlayerInfo::SetPlayerPawn(AFFPlayerPawn* _Pawn)
{
	Pawn = _Pawn;
}

AFFSector* UFFPlayerInfo::GetCurrentSector() const
{
	return (Pawn != nullptr ? Pawn->CurrentSector : nullptr);
}

void UFFPlayerInfo::SetCurrentSector(AFFSector* Sector)
{
	Pawn->CurrentSector = Sector;
}

void UFFPlayerInfo::SetCurrentSector(const TCHAR* SectorName)
{
	AFFSector* Sector = FindObject<AFFSector>(GetOuter(), SectorName);

	UWorld* World = Cast<UWorld>(GetOuter());

	if (!Sector)
	{
		for (TActorIterator<AFFSector> It(World); It; ++It)
		{
			if (It->GetName() == SectorName)
			{
				Sector = *It;
				//UE_LOG(Firefly, Log, TEXT("Found Sector %x (%x)"), Sector, Sector->GetOuter());
				break;
			}
		}
	}

	if (Pawn)
		Pawn->CurrentSector = Sector;
}

const AFFEngineCard* UFFPlayerInfo::GetEngine() const
{
	return Engine;
}

void UFFPlayerInfo::Init(APlayerController* PlayerController, const TCHAR* StartSector)
{
	const UFFGameTuning* GameTuning = GetDefaultGameTuning();

	UWorld* World = Cast<UWorld>(GetOuter());
	
	Controller = Cast<AFireflyPlayerController>(PlayerController);
	if (Controller != nullptr)
		Pawn = Cast<AFFPlayerPawn>(Controller->GetPawn());

	if (Pawn == nullptr && World != nullptr)
		Pawn = World->SpawnActor<AFFPlayerPawn>(GameTuning->DefaultPlayerPawn);

	SetCurrentSector(TEXT("A1"));

	if (GetCurrentSector())
		Pawn->SetActorLocation(GetCurrentSector()->GetCenter());

	if (GameTuning->DefaultEngine.GetDefaultObject())
	{
		Engine = World->SpawnActor<AFFEngineCard>(GameTuning->DefaultEngine);
	}
}

