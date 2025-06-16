// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BGame/Utility/CustomDelegates.h"
#include "InputManagerComponent.generated.h"


class APlayerCharacterBase;
class APlayerControllerBase;

class UEnhancedInputLocalPlayerSubsystem;

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
	void Bind(UEnhancedInputComponent* EnhancedInputComponent, class UInputAction* Action, void (UInputManagerComponent::*Func)(const struct FInputActionValue& AxisValue));
	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);

	static void InputBroadcast(const FOnCharacterInputVector2D& InputDelegate, const FVector2D& AxisValue);
	static void InputBroadcast(const FOnPlayerInput& InputDelegate, const bool& InputValue);
	
	void InputMove(const struct FInputActionValue& AxisValue);
	void InputLook(const struct FInputActionValue& AxisValue);
	void InputAttack(const struct FInputActionValue& AxisValue);
	void InputParry(const struct FInputActionValue& AxisValue);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ParryAction;
	////												  ////
	//					Default Variable					// 
	////												  ////
	bool bInitialize = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	bool bInputAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	bool bInputParry = false;
	
public:
	bool IsInputAttack() const { return bInputAttack;}
	bool IsInputParry() const { return bInputParry; }
};
