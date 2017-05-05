// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFActor.h"
#include "FFShip.generated.h"

class AFFShipPlace;
class AFFLeaderCard;
class AFFSector;

/** The Ship Board of each player */
UCLASS(Blueprintable, ClassGroup = "Firefly")
class AFFShip : public AFFActor
{
	GENERATED_BODY()

public:
	AFFShip();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	void SetSector(int32 SectorId);
	void SetSector(const FString& SectorName);
	void SetSector(AFFSector* Sector);

	const AFFSector* GetCurrentSector() const;
	AFFSector* GetCurrentSector();

	UFUNCTION(Reliable, NetMulticast)
	void ClientInitialize(int32 Id);

private:
	void CreateMaterialInstance();

public:
	UPROPERTY(EditAnywhere)
	UTexture* ShipTexture;

private:
	static FName ShipTextureName;

	UPROPERTY()
	UMaterialInstanceDynamic* ShipMaterial;

	UPROPERTY(Replicated)
	int32 PlayerId;

	UPROPERTY(Replicated)
	AFFSector* CurrentSector;
};
