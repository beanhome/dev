// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GSActor.h"
#include "SWActor.generated.h"

/**
 * 
 */
UCLASS()
class SHADOWWAR_API ASWActor : public AGSActor
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	
	void SetOutline(bool bEnable, int32 iStencilValue = -1);

private:
	UPROPERTY(EditAnywhere)
	TArray<FString> OutlineMeshesNames;

	UPROPERTY()
	TArray<UPrimitiveComponent*> OutlineMeshes;
};
