// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFPlayerInfo.generated.h"

class AFFPlayerPawn;
class AFireflyPlayerController;
class AFFSector;
class AFFCard;
class AFFEngineCard;

UCLASS(minimalapi)
class UFFPlayerInfo : public UObject
{
	GENERATED_BODY()

public:
	UFFPlayerInfo();

	int32 GetId() const;
	const AFireflyPlayerController* GetController() const;

	void Init(APlayerController* PlayerController, const TCHAR* StartSector);

	void SetPlayerPawn(AFFPlayerPawn* _Pawn);
	void SetId(int32 id);

	AFFSector* GetCurrentSector() const;

	void SetCurrentSector(AFFSector* Sector);
	void SetCurrentSector(const TCHAR* SectorName);

	const AFFEngineCard* GetEngine() const;
	
private:
	UPROPERTY()
	int32 Id;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	AFireflyPlayerController* Controller;

	UPROPERTY()
	AFFPlayerPawn* Pawn;

	UPROPERTY()
	int32 Money;

	UPROPERTY()
	AFFEngineCard* Engine;

	UPROPERTY()
	TArray<AFFCard*> ShipUpgrade;

	UPROPERTY()
	AFFCard* Leader;

	UPROPERTY()
	TArray<AFFCard*> Crews;

	// Cargo
	// ...

	UPROPERTY()
	TArray<AFFCard*> HandleJobs;

	UPROPERTY()
	TArray<AFFCard*> ActiveJobs;

	UPROPERTY()
	TArray<AFFCard*> HandleCards;

	UPROPERTY()
	int32 WarrentCount;
};



