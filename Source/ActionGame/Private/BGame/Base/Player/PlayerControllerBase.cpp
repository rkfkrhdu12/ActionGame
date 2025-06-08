// Fill out your copyright notice in the Description page of Project Settings.

#include "BGame/Base/Player/PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "BGame/Base/Player/InputManagerComponent.h"


APlayerControllerBase::APlayerControllerBase()
{
	InputManager = CreateDefaultSubobject<UInputManagerComponent>(TEXT("InputManager"));
}

void APlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	MyCharacter = Cast<APlayerCharacterBase>(aPawn);
	InitializeInputSystem();
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	BindInputActions();
}

//					   Input System						
void APlayerControllerBase::InitializeInputSystem() const
{
	if (MyCharacter && InputManager)
	{
		InputManager->Initialize(MyCharacter, ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()));
	}
}

void APlayerControllerBase::BindInputActions() const
{
	if (InputManager)
		InputManager->BindActions(Cast<UEnhancedInputComponent>(InputComponent));
}
