// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputType.h"
#include "BGame/Utility/CustomDelegates.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerBase();

	///////////////////////// Input
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInputVector2D OnInputLookDirection;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInputVector2D OnInputMoveDirection;

	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnInputAttack;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnInputParry;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnInputDash;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnInputLookAtTarget;
	
protected: 
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

protected:
	//			 
	//				Other Object ptr Variable			
	//											 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class APlayerCharacterBase> MyCharacter;

	//					   Input Manager					  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputManagerComponent> InputManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bCanMove = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bCanMoveCamera = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bIsLookAtTarget = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	AActor* LookAtTarget = nullptr;
private:
	void InitializeInputSystem() const;
	void BindInputActions() const;

public:
	UInputManagerComponent* GetInputManagerComponent() const { return InputManager; }
	bool IsLookAtTarget() const { return bIsLookAtTarget; }
};
