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

void UInputManagerComponent::BindActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UInputManagerComponent::InputMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputManagerComponent::InputLook);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &UInputManagerComponent::InputAttack);
	}
}

void UInputManagerComponent::InputBroadcast(const FOnInputKeyVector2D& InputDelegate, const FVector2D& AxisValue)
{
	InputDelegate.Broadcast(AxisValue);
}

void UInputManagerComponent::InputBroadcast(const FOnInputKey& InputDelegate, const bool& InputValue)
{
	InputDelegate.Broadcast(InputValue);
}


// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::InputMove(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(OnInputMoveDirection, AxisValue.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::InputLook(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(OnInputLookDirection, AxisValue.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::InputAttack(const struct FInputActionValue& AxisValue)
{
	bInputAttack = AxisValue.Get<bool>();
	
	InputBroadcast(OnInputAttack, bInputAttack);
}
