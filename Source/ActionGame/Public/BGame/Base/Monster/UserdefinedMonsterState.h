// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/UserdefinedState.h"
#include "UserdefinedMonsterState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUserdefinedMonsterState : public UUserdefinedState
{
	GENERATED_BODY()
public:
	virtual void Initialize(ACharacterBase* Character) override;
	virtual bool IsValidValues() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlledObject")
	class AMonsterCharacterBase* MyMonsterCharacter = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlledObject")
	class AAIController* MyAIController = nullptr;
	
};
