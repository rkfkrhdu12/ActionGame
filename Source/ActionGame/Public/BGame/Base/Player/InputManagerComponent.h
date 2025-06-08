// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputManagerComponent.generated.h"


class APlayerCharacterBase;
class APlayerControllerBase;

class UEnhancedInputLocalPlayerSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputKeyVector2D, FVector2D, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputKey, bool, InputValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputManagerComponent();
public:
	void Initialize(APlayerCharacterBase* Player, UEnhancedInputLocalPlayerSubsystem* Subsystem);

public:
	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);

	static void InputBroadcast(const FOnInputKeyVector2D& InputDelegate, const FVector2D& AxisValue);
	static void InputBroadcast(const FOnInputKey& InputDelegate, const bool& InputValue);
	
	void InputMove(const struct FInputActionValue& AxisValue);
	void InputLook(const struct FInputActionValue& AxisValue);
	void InputAttack(const struct FInputActionValue& AxisValue);

public:
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnInputKeyVector2D OnInputMoveDirection;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnInputKeyVector2D OnInputLookDirection;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnInputKey OnInputAttack;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TObjectPtr<APlayerCharacterBase> MyCharacter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TObjectPtr<APlayerControllerBase> MyController;
	
	////												  ////
	//		 	    Input BlueprintEdit Variable			// 
	////												  ////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> CurrentMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;
	
	////												  ////
	//					Default Variable					// 
	////												  ////
	bool bInitialize = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	bool bInputAttack = false;
public:
	bool IsInputAttack() const { return bInputAttack;}
};
