// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputType.h"
#include "Components/ActorComponent.h"
#include "BGame/Utility/CustomDelegates.h"
#include "InputManagerComponent.generated.h"


struct FInputActionInstance;
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

	void Move(const struct FInputActionValue& AxisValue);
	void Look(const struct FInputActionValue& AxisValue);
	void Attack(const struct FInputActionValue& AxisValue);
	void Parry(const struct FInputActionValue& AxisValue);
	void Dash(const struct FInputActionValue& AxisValue);
	void LookAtTarget(const struct FInputActionValue& AxisValue);
	
protected:
	static void InputBroadcast(const FOnCharacterInputVector2D* InputDelegate, const FVector2D AxisValue);
	static void InputBroadcast(const FOnCharacterInput* InputDelegate, const bool InputValue);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TMap<EPlayerInputType, UInputAction*> InputMappings;
	////												  ////
	//					Default Variable					//
	////												  ////
	bool bInitialize = false;
};
