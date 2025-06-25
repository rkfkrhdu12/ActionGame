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
		UE_LOG(LogTemp, Error, TEXT("UInputManagerComponent::Bind: Action is null")); return;
	}
	
	EnhancedInputComponent->BindAction(Action, ETriggerEvent::Triggered, this, Func);
}

void UInputManagerComponent::BindActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	constexpr std::pair<EPlayerInputType, void (UInputManagerComponent::*)(const FInputActionValue&)> BindPairs[] = {
	{ EPlayerInputType::Move, &UInputManagerComponent::Move },
	{ EPlayerInputType::Look, &UInputManagerComponent::Look },
	{ EPlayerInputType::Attack, &UInputManagerComponent::Attack },
	{ EPlayerInputType::Parry, &UInputManagerComponent::Parry },
	{ EPlayerInputType::Dash, &UInputManagerComponent::Dash },
	{ EPlayerInputType::LookAtTarget, &UInputManagerComponent::LookAtTarget },
	};

	for (const auto& Pair : BindPairs)
	{
		if (InputMappings.Contains(Pair.first)) Bind(EnhancedInputComponent, InputMappings[Pair.first], Pair.second);
	}
}

void UInputManagerComponent::InputBroadcast(const FOnCharacterInputVector2D* InputDelegate, const FVector2D AxisValue)
{
	if (InputDelegate == nullptr) return;
	
	InputDelegate->Broadcast(AxisValue);
}

void UInputManagerComponent::InputBroadcast(const FOnCharacterInput* InputDelegate, const bool InputValue)
{
	if (InputDelegate == nullptr) return;
	
	InputDelegate->Broadcast(InputValue);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::Move(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(&MyController->OnInputMoveDirection, AxisValue.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::Look(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(&MyController->OnInputLookDirection, AxisValue.Get<FVector2D>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::Attack(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(&MyController->OnInputAttack, AxisValue.Get<bool>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::Parry(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(&MyController->OnInputParry, AxisValue.Get<bool>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::Dash(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(&MyController->OnInputDash, AxisValue.Get<bool>());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInputManagerComponent::LookAtTarget(const struct FInputActionValue& AxisValue)
{
	InputBroadcast(&MyController->OnInputLookAtTarget, AxisValue.Get<bool>());
}
