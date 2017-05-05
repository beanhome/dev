// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "FFGameSequence.generated.h"

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

#define SEQLOG() Log(__FUNCTION__)
#define SEQLOG2(str) Log(FString(__FUNCTION__) + "  " + str)

UCLASS(minimalapi)
class AFFGameSequence : public AActor
{
	GENERATED_BODY()

	friend class AFireflyPlayerController;

public:
	AFFGameSequence();
	virtual void PostActorCreated() override;
	virtual void Destroyed() override;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	void Log(const FString& str) const;
	void Log(const FString& str, const FString& format, ...) const;

	template<class T>
	T* GetOwner()
	{
		return Cast<T>(AActor::GetOwner());
	}

	template<class T>
	const T* GetOwner() const
	{
		return Cast<T>(AActor::GetOwner());
	}

public:
	virtual bool IsCameraFree() const;
	bool IsUnderCamera(const FString& CameraName) const;

	void DrawDebug(class UCanvas* Canvas, float& x, float& y) const;

protected:
	bool IsServer() const;
	bool IsClient() const;
	bool IsLocal() const;

	AFireflyPlayerController* GetFFPlayerController() const;
	int32 GetMyPlayerId() const;

	FString GetMultiMode() const;

	virtual void Init(AFFGameSequence* OwnerSequence);
	virtual void Start();
	virtual void End();
	
	virtual void ServerInit(AFFGameSequence* OwnerSequence);
	virtual void ServerStart();
	virtual void ServerEnd();
	virtual void ServerOnAllClientSynchro(EFFClientGameSeqState NewState);

	void SendResponseToServer(int32 res);
	void ServerStopCurrentSequence();

	// from player controller
	virtual void ServerReceiveResponse(int32 res);
	void ServerReceiveClientState(int32 id, EFFClientGameSeqState NewState);
	/*
	void ServerReceiveMouseEnterActor(int32 PlayerId, class AFFActor* Actor);
	void ServerReceiveMouseExitActor(int32 PlayerId, class AFFActor* Actor);
	void ServerReceiveMouseClickActor(int32 PlayerId, class AFFActor* Actor);
	*/

	AFFGameSequence* StartSubSequence(UClass* Class);
	void StopSubSequence(AFFGameSequence* SubSequence);
	void OnSubSequenceStopped(AFFGameSequence* SubSequence);
	void OnSubSequenceEnded(AFFGameSequence* SubSequence);

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
		SubSequences.Add(Seq);
		return Seq;
	}

	void StopLocalSubSequence(AFFGameSequence* SubSequence);

public:
	// return true if capture the event
	virtual bool PropagateMouseEnterActor(int32 PlayerId, class AFFActor* Actor);
	virtual bool PropagateMouseLeaveActor(int32 PlayerId, class AFFActor* Actor);
	virtual bool PropagateMouseClickActor(int32 PlayerId, class AFFActor* Actor);

protected:
	// return true if capture the event
	virtual bool OnMouseEnterActor(int32 PlayerId, class AFFActor* Actor);
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AFFActor* Actor);
	virtual bool OnMouseClickActor(int32 PlayerId, class AFFActor* Actor);

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
	TArray<AFFGameSequence*> SubSequences;

	EFFClientGameSeqState State; // Server : Min Client State // Client : self State
	TMap<int32, EFFClientGameSeqState> ClientState;

public:
	UPROPERTY()
	FFFSequenceFinishDelegate EndDelegate;
};



