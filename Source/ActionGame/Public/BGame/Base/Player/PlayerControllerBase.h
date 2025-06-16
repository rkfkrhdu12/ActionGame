// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	FOnPlayerInput OnAttack;
	FOnPlayerInput OnParry;
	
protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

	void InputAttack(bool Value);
	UFUNCTION(BlueprintCallable, Category = Input, BlueprintImplementableEvent)
	void OnInputKeyAttack(bool Value);
	void InputParry(bool Value);
	UFUNCTION(BlueprintCallable, Category = Input, BlueprintImplementableEvent)
	void OnInputKeyParry(bool Value);
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
	bool IsCanMove = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool IsCanMoveCamera = true;
	
private:
	void InitializeInputSystem() const;
	void BindInputActions() const;

public:
	UInputManagerComponent* GetInputManagerComponent() const { return InputManager; }
};
