// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFTypes.h"
#include "FFShipBoard.generated.h"

USTRUCT()
struct FFFCargo
{
	GENERATED_BODY()

	UPROPERTY()
	class UStaticMeshComponent* BigLoc;
	
	UPROPERTY()
	class UStaticMeshComponent* HalfLoc0;
	
	UPROPERTY()
	class UStaticMeshComponent* HalfLoc1;

	UPROPERTY()
	class AFFStuff* First;

	UPROPERTY()
	class AFFStuff* Second;

	bool AddStuff(AFFStuff* stuff);
	bool RemStuff(AFFStuff* stuff);
};

/** The Ship Board of each player */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFShipBoard : public AFFActor
{
	GENERATED_BODY()

public:
	AFFShipBoard();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UFUNCTION(Reliable, NetMulticast)
	void ClientInitialize(int32 Id, const struct FFFPlayer& Player);

	class AFFEngineCard* GetEngine() const;

	bool AddStuff(TSubclassOf<class AFFStuff> stuff, int32 count);
	bool AddStuff(TSubclassOf<class AFFStuff> stuff);
	bool AddStuff(class AFFStuff* stuff);
	bool RemStuff(TSubclassOf<class AFFStuff> stuff);
	bool RemStuff(class AFFStuff* stuff);
	bool HasStuff(TSubclassOf<class AFFStuff> stuff, int32 nb = 1);

	void AddCrew(TSubclassOf<class AFFCrewCard> CardClass);
	void AddCardToHand(TSubclassOf<class AFFSupplyCard> CardClass);

	const TArray<class AFFCrewCard*>& GetCrew() const;
	int32 GetMaxCrew() const;

	void InitCargo();

	UFUNCTION(Reliable, NetMulticast)
	void RefreshCredits(int32 Credits);

	void MakeAllCrewDisgruntled();
	void RemoveAllDisgruntled();

private:
	void CreateMaterialInstance();

	bool Stock(TArray<FFFCargo>& _Cargo, TArray<FFFCargo>& _Stash, const TArray<class AFFStuff*>& _Stuffs) const;

	bool TestCargo(const TArray<class AFFStuff*>& _Stuffs) const;
	bool TestAddCargo(class AFFStuff* _Stuff, int32 iCount = 1) const;
	bool TestAddCargo(const TArray<class AFFStuff*>& _Stuffs) const;

	bool Stock();
	bool StockNewStuffs(const TArray<class AFFStuff*>& _Stuffs);
	bool StockNewStuffs(class AFFStuff* _Stuff, int32 iCount = 1);

	UFUNCTION(Reliable, NetMulticast)
	void RefreshCargo();

	UFUNCTION()
	void OnRep_RefreshCargo();

	UFUNCTION()
	void OnRep_SetEngine();

	UFUNCTION()
	void OnRep_SetCrew();

public:
	UPROPERTY(EditAnywhere)
	UTexture* FrontTexture;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFShip> DefaultShip;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFEngineCard> DefaultEngine;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AFFStuff> > DefaultStuffs;

	UPROPERTY(EditAnywhere)
	int32 MaxCrew;

	UPROPERTY(EditAnywhere)
	int32 MaxShipUpgrade;

private:
	static FName FrontTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* FrontMaterial;

	UPROPERTY(Replicated)
	int32 PlayerId;

	UPROPERTY()
	class AFFLeaderCard* Leader;

	UPROPERTY(ReplicatedUsing = OnRep_SetCrew)
	TArray<class AFFCrewCard*> Crew;

	UPROPERTY(Replicated)
	TArray<class AFFSupplyCard*> Hand;

	UPROPERTY(ReplicatedUsing = OnRep_SetEngine)
	class AFFEngineCard* Engine;

	UPROPERTY()
	TMap<int32, class AFFShipBoardPlace*> ShipBoardPlaces;
	
	UPROPERTY()
	class AFFShipBoardPlace* ShipBoardPlace;

	UPROPERTY()
	TArray<FFFCargo> Cargo;

	UPROPERTY()
	TArray<FFFCargo> Stash;

	UPROPERTY()
	UTextRenderComponent* CreditsText;

	UPROPERTY(ReplicatedUsing = OnRep_RefreshCargo)
	TArray<class AFFStuff*> Stuffs;
};
