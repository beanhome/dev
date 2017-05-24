// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFShipBoard.generated.h"

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
	void ClientInitialize(int32 Id, class AFFLeaderCard* _Leader, class AFFEngineCard* _Engine);

	class AFFEngineCard* GetEngine() const;

private:
	void CreateMaterialInstance();

	UFUNCTION()
	void OnRep_SetEngine();

public:
	UPROPERTY(EditAnywhere)
	UTexture* FrontTexture;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFShip> DefaultShip;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFFEngineCard> DefaultEngine;

private:
	static FName FrontTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* FrontMaterial;

	UPROPERTY(Replicated)
	int32 PlayerId;

	UPROPERTY()
	class AFFLeaderCard* Leader;

	UPROPERTY(ReplicatedUsing = OnRep_SetEngine)
	class AFFEngineCard* Engine;

	UPROPERTY()
	TMap<int32, class AFFShipBoardPlace*> ShipBoardPlaces;
	
	UPROPERTY()
	class AFFShipBoardPlace* ShipBoardPlace;
};
