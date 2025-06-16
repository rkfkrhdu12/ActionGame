// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Player/InputManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "BGame/Base/Player/PlayerControllerBase.h"

UInputManagerComponent::UInputManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInputManagerComponent::Initialize(APlayerCharacterBase* Player, UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	MyCharacter = Player;
	if (MyCharacter == nullptr || Subsystem == nullptr) return;

	Subsystem->AddMappingContext(CurrentMappingContext.Get(), 0);

	MyController = Cast<APlayerControllerBase>(MyCharacter->GetController());
}

void UInputManagerComponent::Bind(UEnhancedInputComponent* EnhancedInputComponent, class UInputAction* Action,
	void(UInputManagerComponent::* Func)(const struct FInputActionValue& AxisValue))
{
	if (!EnhancedInputComponent) return;

	if (Action == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UInputManagerComponent::Bind: Action is null"));
		return;
	}

	EnhancedInputComponent->BindAction(Action, ETriggerEvent::Triggered, this,
		Func);
}


void UInputManagerComponent::BindActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent)
	{
		Bind(EnhancedInputComponent,MoveAction, &UInputManagerComponent::InputMove);
		Bind(EnhancedInputComponent,LookAction, &UInputManagerComponent::InputLook);
		Bind(EnhancedInputComponent,AttackAction, &UInputManagerComponent::InputAttack);
		Bind(EnhancedInputComponent,ParryAction, &UInputManagerComponent::InputParry);
	}
}

void UInputManagerComponent::InputBroadcast(const FOnCharacterInputVector2D& InputDelegate, const FVector2D& AxisValue)
{
	InputDelegate.Broadcast(AxisValue);
}

void UInputManagerComponent::InputBroadcast(const FOnPlayerInput& InputDelegate, const bool& InputValue)
{
	InputDelegate.Broadcast(InputValue);
}


// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::InputMove(const struct FInputActionValue& AxisValue)
{
	if (!MyController) return;
	
	InputBroadcast(MyController->OnInputMoveDirection, AxisValue.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::InputLook(const struct FInputActionValue& AxisValue)
{
	if (!MyController) return;
	
	InputBroadcast(MyController->OnInputLookDirection, AxisValue.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::InputAttack(const struct FInputActionValue& AxisValue)
{
	if (!MyController) return;
	
	bInputAttack = AxisValue.Get<bool>();
	
	InputBroadcast(MyController->OnAttack, bInputAttack);
}

void UInputManagerComponent::InputParry(const struct FInputActionValue& AxisValue)
{
	if (!MyController) return;
	
	bInputParry = AxisValue.Get<bool>();
	
	InputBroadcast(MyController->OnParry, bInputParry);
	
}
