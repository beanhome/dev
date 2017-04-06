// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFGameSequence.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseEnterSectorDelegate, AFFSector*, Sector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseExitSectorDelegate, AFFSector*, Sector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseClickSectorDelegate, AFFSector*, Sector);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFFSequenceFinishDelegate, AFFGameSequence*, Seq);

class AFireflyPlayerController;

UENUM()
enum class EFFClientGameSeqState : uint8
{
	None,
	Spawned,
	Initialized,
	Started,
	Ended,
};

UCLASS(minimalapi)
class AFFGameSequence : public AActor
{
	GENERATED_BODY()

	friend class AFireflyPlayerController;

public:
	AFFGameSequence();
	virtual void PostActorCreated() override;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	template<class T>
	T* GetOwner()
	{
		return Cast<T>(AActor::GetOwner());
	}

public:
	void OnMouseEnterSector(AFFSector* Sector);
	void OnMouseExitSector(AFFSector* Sector);
	void OnMouseClickSector(AFFSector* Sector);

protected:
	bool IsServer() const;
	bool IsClient() const;
	bool IsLocal() const;

	AFireflyPlayerController* GetFFPlayerController() const;
	int32 GetPlayerId() const;

	FString GetMultiMode() const;

	virtual void Init(AFFGameSequence* OwnerSequence);
	virtual void Start();
	virtual void End();
	
	virtual void ServerInit(AFFGameSequence* OwnerSequence);
	virtual void ServerStart();
	virtual void ServerEnd();
	virtual void ServerOnAllClientSynchro(EFFClientGameSeqState NewState);

	void SendResponseToServer(int32 res);

	// from player controller
	virtual void ServerReceiveResponse(int32 res);
	void ServerReceiveClientState(int32 id, EFFClientGameSeqState NewState);

	void ServerStopCurrentSequence();

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
		Seq->InitWithParam(this, Init);
		Seq->Start();
		SubSequence = Seq;
		return Seq;
	}

private:
	void SetState(EFFClientGameSeqState NewState);

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

	EFFClientGameSeqState State; // Server : Min Client State // Client : self State
	TMap<int32, EFFClientGameSeqState> ClientState;

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



