// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/UserdefinedState.h"
#include "UserdefinedPlayerStateBase.generated.h"

class APlayerControllerBase;
class UInputManagerComponent;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUserdefinedPlayerStateBase : public UUserdefinedState
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacterBase* Character) override;
	virtual bool IsValidValues() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerControllerBase> MyPlayerController = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputManagerComponent> InputManager = nullptr;
};

