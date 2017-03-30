// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Firefly.h"
#include "FFGameSequence.h"
#include "UnrealNetwork.h"
#include "Game/FireflyPlayerController.h"

AFFGameSequence::AFFGameSequence()
: SubSequence(nullptr)
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	bAlwaysRelevant = true;
}

bool AFFGameSequence::IsSupportedForNetworking() const
{
	return true;
}

void AFFGameSequence::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AFFGameSequence, SubSequence);
}

AFireflyPlayerController* AFFGameSequence::GetFFPlayerController() const
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	return (GameInstance != nullptr ? Cast<AFireflyPlayerController>(GameInstance->GetFirstLocalPlayerController(GetWorld())) : nullptr);
}

void AFFGameSequence::ServerInit(AFFGameSequence* OwnerSequence)
{
	SetOwner(OwnerSequence);
	ClientInit(OwnerSequence);
}

void AFFGameSequence::ServerStart()
{
	ClientStart();
}

void AFFGameSequence::ServerEnd()
{
	ClientEnd();
}

void AFFGameSequence::Init(AFFGameSequence* OwnerSequence)
{
	if (OwnerSequence)
		SetOwner(OwnerSequence);
}

void AFFGameSequence::Start()
{

}

void AFFGameSequence::End()
{
}

void AFFGameSequence::ServerReceiveResponse(int32 res)
{
	if (SubSequence)
		SubSequence->ServerReceiveResponse(res);
}

void AFFGameSequence::ServerStopCurrentSequence()
{
	if (SubSequence)
	{
		SubSequence->ServerStopCurrentSequence();
	}

	ServerEnd();
	EndDelegate.Broadcast(this);
}

AFFGameSequence* AFFGameSequence::StartSubSequence(UClass* Class)
{
	FActorSpawnParameters Param;
	Param.Owner = this;
	SubSequence = CastChecked<AFFGameSequence>(GetWorld()->SpawnActor(Class, nullptr, nullptr, Param));
	SubSequence->ServerInit(this);
	SubSequence->ServerStart();

	return SubSequence;
}

void AFFGameSequence::StopSubSequence()
{
	SubSequence->ServerEnd();
	SubSequence->Destroy();
	SubSequence = nullptr;
}

void AFFGameSequence::OnMouseEnterSector(AFFSector* Sector)
{
	MouseEnterSector.Broadcast(Sector);

	if (SubSequence)
		SubSequence->OnMouseEnterSector(Sector);
}

void AFFGameSequence::OnMouseExitSector(AFFSector* Sector)
{
	MouseExitSector.Broadcast(Sector);

	if (SubSequence)
		SubSequence->OnMouseExitSector(Sector);
}

void AFFGameSequence::OnMouseClickSector(AFFSector* Sector)
{
	MouseClickSector.Broadcast(Sector);

	if (SubSequence)
		SubSequence->OnMouseClickSector(Sector);
}

void AFFGameSequence::ClientInit_Implementation(AFFGameSequence* OwnerSequence)
{
	Init(OwnerSequence);
}

void AFFGameSequence::ClientStart_Implementation()
{
	Start();
}

void AFFGameSequence::ClientEnd_Implementation()
{
	End();
}
