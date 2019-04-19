// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GSSequence.generated.h"

DECLARE_DELEGATE_OneParam(FGSSequenceFinishDelegate, class AGSSequence*);
DECLARE_DELEGATE_RetVal_OneParam(bool, FGSSubSequenceFinishDelegate, class AGSSequence*);


class AGSPlayerController;

UENUM()
enum class EGSClientState : uint8
{
	None,
	Spawned,
	Initialized,
	Started,
	Ended,
};

#define SEQLOG() Log(__FUNCTION__)
#define SEQLOG2(str) Log(FString(__FUNCTION__) + "  " + str)

// Base class of all T::FInit
struct FGSSequenceInit { };

// Struct to build sequencial sub sequence
USTRUCT()
struct FGSSequenceDefinition
{
	GENERATED_BODY()

	class UClass* Class;
	struct FGSSequenceInit* Param;
	FGSSubSequenceFinishDelegate EndCallBack;
};

// Struct Response
USTRUCT()
struct FGSResponse
{
	GENERATED_BODY()

	FGSResponse() : Int(0), Float(0.f), Location(FVector::ZeroVector), Rotation(FRotator::ZeroRotator) {}


	UPROPERTY()
	int32 Int;

	UPROPERTY()
	float Float;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;
};

UCLASS()
class GAMESEQUENCE_API AGSSequence : public AActor
{
	GENERATED_BODY()

	friend class AGSPlayerController;

public:
	AGSSequence();
	virtual void PostActorCreated() override;
	virtual void Destroyed() override;

	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	void Log(const FString& str) const;
	void Log(const FString& str, const FString& format, ...) const;

	template<class T>
	T* GetOwner() const;

	AGSSequence* FindSubSequence(UClass* Class) const;

	template<class T>
	T* FindSubSequence() const;

public:
	virtual bool IsActorInteractive() const;

	void DrawDebug(class UCanvas* Canvas, float& x, float& y) const;

protected:
	bool IsServer() const;
	bool IsClient() const;
	bool IsLocal() const;

	AGSPlayerController* GetGSPlayerController() const;
	int32 GetMyPlayerId() const;

	FString GetMultiMode() const;

	virtual void DrawDebugSpecific(class UCanvas* Canvas, float& x, float& y) const;

	virtual void Init(AGSSequence* OwnerSequence);
	virtual void Start();
	virtual void End();
	virtual void Suspend();
	virtual void Resume();
	
	virtual void ServerInit(AGSSequence* OwnerSequence);
	virtual void ServerStart();
	virtual void ServerEnd();
	virtual void ServerSuspend();
	virtual void ServerResume();

	virtual void ServerOnAllClientSynchro(EGSClientState NewState);

	void SendResponseToServer(FGSResponse res);
	void ServerStopCurrentSequence();
	void ClientStopSequence();

	// from player controller
	virtual void ServerReceiveResponse(FGSResponse res);
	void ServerReceiveClientState(int32 id, EGSClientState NewState);

	AGSSequence* StartSubSequence(UClass* Class, FGSSequenceInit* Param = nullptr);
	void StopSubSequence(AGSSequence* SubSequence);
	void OnSubSequenceEnded(AGSSequence* SubSequence);

	template <class T>
	T* StartSubSequence(UClass* Class = nullptr, FGSSequenceInit* Param = nullptr);

	template <class UserClass>
	AGSSequence* StartSubSequence(UClass* Class, UserClass* InObj, typename FGSSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr);

	template <class T, class UserClass>
	T* StartSubSequence(const typename T::FInit& _Param, UserClass* InObj, typename FGSSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr);
	
	template <class T>
	T* StartSubSequence(const typename T::FInit& _Param);

	template <class T>
	T* StartLocalSubSequence(UClass* Class, const typename T::FInit& Init);

	template <class T, class UserClass>
	T* StartLocalSubSequence(UClass* Class, const typename T::FInit& Init, UserClass* InObj, typename FGSSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr);

	void LocalStopCurrentSequence();

	void StopLocalSubSequence(AGSSequence* SubSequence);

	void AddSubSequence(UClass* Class, FGSSequenceInit* Param = nullptr);

	template <class T>
	void AddSubSequence();

	template <class T>
	void AddSubSequence(const typename T::FInit& _Param);
	
	template <class T, class UserClass>
	void AddSubSequence(UserClass* InObj, typename FGSSubSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr);

	template <class T, class UserClass>
	void AddSubSequence(const typename T::FInit& _Param, UserClass* InObj, typename FGSSubSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr);

	void StopAutoAfterAllSubSequence(bool bEnable = true);
	void StartSubSequence(int32 id);
	void StartAllSubSequence();

public:
	// return true if capture the event
	virtual bool PropagateMouseEnterActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool PropagateMouseLeaveActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool PropagateMouseClickActor(int32 PlayerId, class AGSActor* Actor);

protected:
	// return true if capture the event
	virtual bool OnMouseEnterActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseLeaveActor(int32 PlayerId, class AGSActor* Actor);
	virtual bool OnMouseClickActor(int32 PlayerId, class AGSActor* Actor);

private:
	void SetState(EGSClientState NewState);

	FGSSequenceDefinition& AddSubSequence_Intern(UClass* Class, FGSSequenceInit* Param = nullptr);

	UFUNCTION()
	void CurrentSubSequenceFinish(AGSSequence* Seq);

private:
	UFUNCTION(Reliable, NetMulticast)
	void ClientInit(AGSSequence* OwnerSequence);

	UFUNCTION(Reliable, NetMulticast)
	void ClientStart();

	UFUNCTION(Reliable, NetMulticast)
	void ClientEnd();

	UFUNCTION(Reliable, NetMulticast)
	void ClientSuspend();

	UFUNCTION(Reliable, NetMulticast)
	void ClientResume();

protected:
	FGSSequenceInit* InitParameter; // Param pointer to DownCast in T::FInit / Exist only fo Server

	UPROPERTY(Replicated)
	TArray<AGSSequence*> SubSequences; // List of active parallel sub sequence

	EGSClientState State; // Server : Min Client State // Client : self State
	TMap<int32, EGSClientState> ClientState;

	UPROPERTY()
	TArray<struct FGSSequenceDefinition> SubSeqDefinitions; // Sequencial subsequence definition

	UPROPERTY()
	int32 CurrentSubDef;

	UPROPERTY()
	bool bStopAutoAfterAllSubSequence;

public:
	FGSSequenceFinishDelegate EndDelegate;
};


template<class T>
T* AGSSequence::GetOwner() const
{
	AActor* ActorOwner = AActor::GetOwner();
	if (ActorOwner == nullptr)
		return nullptr;

	check(ActorOwner->IsA(AGSSequence::StaticClass()));

	T* TestOwner = Cast<T>(ActorOwner);

	return (TestOwner != nullptr ? TestOwner : Cast<AGSSequence>(ActorOwner)->GetOwner<T>());
}


template<class T>
T* AGSSequence::FindSubSequence() const
{
	return Cast<T>(FindSubSequence(T::StaticClass()));
}

template <class T>
T* AGSSequence::StartSubSequence(UClass* Class, FGSSequenceInit* Param)
{
	if (Class == nullptr)
		Class = T::StaticClass();

	return CastChecked<T>(StartSubSequence(Class, Param));
}

template <class UserClass>
AGSSequence* AGSSequence::StartSubSequence(UClass* Class, UserClass* InObj, typename FGSSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr)
{
	AGSSequence* Sub = StartSubSequence(Class);
	if (Sub != nullptr)
		Sub->EndDelegate.BindUObject(InObj, InMethodPtr);

	return Sub;
}

template <class T, class UserClass>
T* AGSSequence::StartSubSequence(const typename T::FInit& _Param, UserClass* InObj, typename FGSSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr)
{
	T* Sub = Cast<T>(StartSubSequence(T::StaticClass(), new T::FInit(_Param)));
	if (Sub != nullptr)
		Sub->EndDelegate.BindUObject(InObj, InMethodPtr);

	return Sub;
}

template <class T>
T* AGSSequence::StartSubSequence(const typename T::FInit& _Param)
{
	T* Sub = Cast<T>(StartSubSequence(T::StaticClass(), new T::FInit(_Param)));
	return Sub;
}


template <class T>
T* AGSSequence::StartLocalSubSequence(UClass* Class, const typename T::FInit& Init)
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	T* Seq = CastChecked<T>(GetWorld()->SpawnActor(Class, nullptr, nullptr, SpawnParam));
	Seq->InitParameter = new T::FInit(Init);
	Seq->Init(this);
	Seq->Start();
	SubSequences.Add(Seq);
	if (SubSequences.Num() == 1)
		Suspend();
	return Seq;
}

template <class T, class UserClass>
T* AGSSequence::StartLocalSubSequence(UClass* Class, const typename T::FInit& Init, UserClass* InObj, typename FGSSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr)
{
	T* Seq = StartLocalSubSequence<T>(Class, Init);
	if (Seq != nullptr)
		Seq->EndDelegate.BindUObject(InObj, InMethodPtr);
	return Seq;
}

template <class T>
void AGSSequence::AddSubSequence()
{
	AddSubSequence_Intern(T::StaticClass());
}

template <class T>
void AGSSequence::AddSubSequence(const typename T::FInit& _Param)
{
	AddSubSequence_Intern(T::StaticClass(), new T::FInit(_Param));
}


template <class T, class UserClass>
void AGSSequence::AddSubSequence(UserClass* InObj, typename FGSSubSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr)
{
	FGSSequenceDefinition& Def = AddSubSequence_Intern(T::StaticClass());
	Def.EndCallBack.BindUObject(InObj, InMethodPtr);
}

template <class T, class UserClass>
void AGSSequence::AddSubSequence(const typename T::FInit& _Param, UserClass* InObj, typename FGSSubSequenceFinishDelegate::TUObjectMethodDelegate< UserClass >::FMethodPtr InMethodPtr)
{
	FGSSequenceDefinition& Def = AddSubSequence_Intern(T::StaticClass(), new T::FInit(_Param));
	Def.EndCallBack.BindUObject(InObj, InMethodPtr);
}

