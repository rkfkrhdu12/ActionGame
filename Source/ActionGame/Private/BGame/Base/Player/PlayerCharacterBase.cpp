// Fill out your copyright notice in the Description page of Project Settings.

#include "BGame/Base/Player/PlayerCharacterBase.h"

#include "BGame/Base/AnimInstanceBase.h"
#include "BGame/Base/StateEventHandle.h"
#include "BGame/Base/Player/PlayerControllerBase.h"
#include "BGame/Base/Player/PlayerStateManagerComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#define AssignDefaultSubobject(Variable)\
Variable = CreateDefaultSubobject<std::remove_reference_t<decltype(*Variable)>>(#Variable)


APlayerCharacterBase::APlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArmComponent->SetupAttachment(GetRootComponent());
	CameraArmComponent->TargetArmLength = 400.f;
	CameraArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	StateManagerComp = CreateDefaultSubobject<UPlayerStateManagerComponent>(TEXT("StateManager"));

	if (!StateEventHandler) AssignDefaultSubobject(StateEventHandler);
	
	TestFunc("APlayerCharacterBase Initialize");
}

void APlayerCharacterBase::OnLookAtMode()
{
	if (!MyPlayerController) return;

	if (MyPlayerController->IsLookAtTarget())
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void APlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyPlayerController = Cast<APlayerControllerBase>(NewController);
}
