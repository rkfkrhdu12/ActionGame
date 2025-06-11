// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstanceBase();
	
	virtual void NativeBeginPlay() override;

	FOnMontageStarted MontageStartDelegate;
	FOnMontageEnded MontageEndDelegate;
	FOnMontageBlendedInEnded MontageBlendedInDelegate;
	FOnMontageBlendingOutStarted MontageBlendingOutDelegate;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	TObjectPtr<class ACharacterBase> MyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	TObjectPtr<USkeletalMeshComponent> MyMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TMap<FString, int32> CurrentStateIndexList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	int32 UpperBodyStateIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	int32 LowerBodyStateIndex = 0;
};
