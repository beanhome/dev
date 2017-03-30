// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFGameSequence.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseEnterSectorDelegate, AFFSector*, Sector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseExitSectorDelegate, AFFSector*, Sector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseClickSectorDelegate, AFFSector*, Sector);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFFSequenceFinishDelegate, AFFGameSequence*, Seq);

class AFireflyPlayerController;

UCLASS(minimalapi)
class AFFGameSequence : public AActor
{
	GENERATED_BODY()

public:
	AFFGameSequence();

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	template<class T>
	T* GetOwner()
	{
		return Cast<T>(AActor::GetOwner());
	}

	AFireflyPlayerController* GetFFPlayerController() const;

	virtual void ServerInit(AFFGameSequence* OwnerSequence);
	virtual void ServerStart();
	virtual void ServerEnd();
	virtual void ServerReceiveResponse(int32 res);
	virtual void ServerStopCurrentSequence();

	AFFGameSequence* StartSubSequence(UClass* Class);
	void StopSubSequence();

	template <class T>
	T* StartSubSequence()
	{
		return CastChecked<T>(StartSubSequence(T::StaticClass()));
	}

	template <class T>
	T* StartSubSequence(UClass* Class)
	{
		return CastChecked<T>(StartSubSequence(Class));
	}

	template <class T>
	T* StartLocalSubSequence(UClass* Class, const typename T::FInit& Init)
	{
		FActorSpawnParameters Param;
		Param.Owner = this;
		T* Seq = CastChecked<T>(GetWorld()->SpawnActor(Class, nullptr, nullptr, Param));
		Seq->Init(this, Init);
		Seq->Start();
		SubSequence = Seq;
		return Seq;
	}

public:
	void OnMouseEnterSector(AFFSector* Sector);
	void OnMouseExitSector(AFFSector* Sector);
	void OnMouseClickSector(AFFSector* Sector);

protected:
	virtual void Init(AFFGameSequence* OwnerSequence);
	virtual void Start();
	virtual void End();

private:
	UFUNCTION(Reliable, NetMulticast)
	void ClientInit(AFFGameSequence* OwnerSequence);

	UFUNCTION(Reliable, NetMulticast)
	void ClientStart();

	UFUNCTION(Reliable, NetMulticast)
	void ClientEnd();

protected:
	UPROPERTY(Replicated)
	AFFGameSequence* SubSequence;

public:
	UPROPERTY()
	FMouseEnterSectorDelegate MouseEnterSector;

	UPROPERTY()
	FMouseExitSectorDelegate MouseExitSector;

	UPROPERTY()
	FMouseClickSectorDelegate MouseClickSector;

	UPROPERTY()
	FFFSequenceFinishDelegate EndDelegate;
};



