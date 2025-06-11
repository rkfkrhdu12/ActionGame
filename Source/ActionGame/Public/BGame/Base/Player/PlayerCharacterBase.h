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
	// Look의 경우 Rotate나 Quaternion같은 류가 아닌 마우스의 이동으로 입력받으므로 캐릭터를 분리
	// Not Rotate, Quaternion  LookInput is Mouse MoveDirection(Vector2D)
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInputVector2D OnInputLookDirection;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraArmComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;

	
};
