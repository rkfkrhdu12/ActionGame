// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Player/PlayerAnimInstanceBase.h"

#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "BGame/Base/Player/PlayerControllerBase.h"

void UPlayerAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MyPlayerCharacter = Cast<APlayerCharacterBase>(GetOwningActor());
	if (MyPlayerCharacter)
	{
		MyPlayerController = Cast<APlayerControllerBase>(MyPlayerCharacter->GetController());
	}
}  
