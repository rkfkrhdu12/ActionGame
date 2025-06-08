// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "UserdefinedMontageNotify.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUserdefinedMontageNotify : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
public:
	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	
	virtual FString GetNotifyName_Implementation() const override;
};
