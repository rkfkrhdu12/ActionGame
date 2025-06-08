// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UActionManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	UFUNCTION()
	void AnimMontageStarted(class UAnimMontage* Montage);
	UFUNCTION()
	void AnimMontageEnded(class UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void AnimMontageBlendedIn(class UAnimMontage* Montage);
	UFUNCTION()
	void AnimMontageBlendedOut(class UAnimMontage* Montage, bool bInterrupted);

	
};
