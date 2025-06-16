// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/CharacterBase.h"
#include "PlayerCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacterBase();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraArmComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;

	
};
