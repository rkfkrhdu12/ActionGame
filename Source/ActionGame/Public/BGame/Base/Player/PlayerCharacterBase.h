// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/CharacterBase.h"
#include "PlayerCharacterBase.generated.h"

class APlayerControllerBase;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API APlayerCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacterBase();

	UFUNCTION(BlueprintCallable)
	void OnLookAtMode();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraArmComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller", meta = (AllowPrivateAccess = "true"))
	APlayerControllerBase* MyPlayerController;
};
