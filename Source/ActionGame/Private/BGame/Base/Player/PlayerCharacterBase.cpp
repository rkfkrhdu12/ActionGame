// Fill out your copyright notice in the Description page of Project Settings.

#include "BGame/Base/Player/PlayerCharacterBase.h"

#include "BGame/Base/AnimInstanceBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}
