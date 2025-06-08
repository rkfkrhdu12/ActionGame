// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Player/UserdefinedPlayerStateBase.h"

#include "BGame/Base/Player/PlayerControllerBase.h"

void UUserdefinedPlayerStateBase::Initialize(ACharacterBase* Character)
{
	Super::Initialize(Character);

	if (MyController == nullptr) return;
	MyPlayerController = Cast<APlayerControllerBase>(MyController);
	
	if (MyPlayerController == nullptr) return;
	InputManager = MyPlayerController->GetInputManagerComponent();
}

bool UUserdefinedPlayerStateBase::IsValidValues() const
{
	if (MyCharacter && MyController && MyMesh && MyAnimInstance && InputManager) return true;

	UE_LOG(LogTemp, Warning, TEXT("%s : Invalid State"), *CurrentStateName);

	return false;
}
 