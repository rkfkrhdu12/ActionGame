// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/StateManagerComponent.h"
#include "PlayerStateManagerComponent.generated.h"

class UUserdefinedPlayerStateBase;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API UPlayerStateManagerComponent : public UStateManagerComponent
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void InputAttack(bool Value);
	UFUNCTION()
	void InputParry(bool Value);
	UFUNCTION()
	void InputDash(bool Value);

protected:
	virtual void BeginPlay() override;

public:
	virtual void ChangeState(const FName& NextState) override;

protected:
	UPROPERTY()
	UUserdefinedPlayerStateBase* CurrentPlayerState = nullptr;
};
