// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "FireflyGameMode.generated.h"

class UFFPlayerInfo;
class AFireflyPlayerController;

UENUM()
enum class EFFGamePhase : uint8
{
	Lobby,
	Game,
	PostGame
};


/** GameMode class to specify pawn and playercontroller */
UCLASS(ClassGroup = "Firefly")
class AFireflyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFireflyGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(class UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void StartGame();

	int32 GetPlayerCount();

	const TArray<UFFPlayerInfo*>& GetPlayers() const;
	TArray<UFFPlayerInfo*>& GetPlayers();

	const UFFPlayerInfo* GetPlayerInfo(int32 id) const;
	UFFPlayerInfo* GetPlayerInfo(int32 id);

	const UFFPlayerInfo* GetPlayerInfo(AFireflyPlayerController* PC) const;
	UFFPlayerInfo* GetPlayerInfo(AFireflyPlayerController* PC);

	UFFPlayerInfo* GetActivePlayer() const;
	
private:
	EFFGamePhase GamePhase;

	int32 TurnNumber;
	int32 PlayerActive;

	UPROPERTY()
	AFireflyPlayerController* HostPlayer;

	UPROPERTY()
	TArray<UFFPlayerInfo*> Players;

	UPROPERTY()
	int32 PlayerCount;
};



