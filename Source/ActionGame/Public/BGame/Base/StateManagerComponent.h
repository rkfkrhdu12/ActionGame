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

	void ChangeState(const FName& NextState);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APlayerCharacterBase* MyCharacter = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APlayerControllerBase* MyController = nullptr;
	void InitializeComponents();


	FName CurrentState = "";
	
};
