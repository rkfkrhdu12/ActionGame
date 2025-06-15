// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UStateManagerComponent();

	UFUNCTION(BlueprintCallable)
	void ChangeState(const FName& NextState);
protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere)
	class ACharacterBase* MyCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	FName CurrentEnableStateName;
};
