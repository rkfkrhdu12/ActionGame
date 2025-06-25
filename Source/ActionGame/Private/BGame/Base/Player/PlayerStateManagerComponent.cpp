// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Player/PlayerStateManagerComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/UserdefinedState.h"

#include "BGame/Base/Player/PlayerControllerBase.h"
#include "BGame/Base/Player/UserdefinedPlayerStateBase.h"

void UPlayerStateManagerComponent::InputAttack(bool Value)
{
	if (CurrentPlayerState) CurrentPlayerState->InputKey(EPlayerInputType::Attack, Value);
}

void UPlayerStateManagerComponent::InputParry(bool Value)
{
	if (CurrentPlayerState) CurrentPlayerState->InputKey(EPlayerInputType::Parry,Value);
}

void UPlayerStateManagerComponent::InputDash(bool Value)
{
	if (CurrentPlayerState) CurrentPlayerState->InputKey(EPlayerInputType::Dash,Value);
}

void UPlayerStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto MyController = Cast<APlayerControllerBase>(MyCharacter->GetController()))
	{
		MyController->OnInputAttack.AddDynamic(this, &UPlayerStateManagerComponent::InputAttack);
		MyController->OnInputParry.AddDynamic(this, &UPlayerStateManagerComponent::InputParry);
		MyController->OnInputDash.AddDynamic(this, &UPlayerStateManagerComponent::InputDash);
	}
}

void UPlayerStateManagerComponent::ChangeState(const FName& NextState)
{
	Super::ChangeState(NextState);

	if (CurrentState) CurrentPlayerState = Cast<UUserdefinedPlayerStateBase>(CurrentState);
}
