// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/AnimInstanceBase.h"
#include "PlayerAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UPlayerAnimInstanceBase : public UAnimInstanceBase
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character", meta=(AllowPrivateAccess=true))
	class APlayerCharacterBase* MyPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controller", meta=(AllowPrivateAccess=true))
	class APlayerControllerBase* MyPlayerController;
};
