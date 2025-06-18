// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Player/UserdefinedPlayerStateBase.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "BGame/Base/Player/PlayerControllerBase.h"

void UUserdefinedPlayerStateBase::Initialize(ACharacterBase* Character)
{
	if (!Character) return;
	
	MyCharacter = Character;
	MyPlayerCharacter = Cast<APlayerCharacterBase>(Character);
	if (MyCharacter)
	{
		if (auto Controller = MyCharacter->GetController())
		{
			MyPlayerController = Cast<APlayerControllerBase>(Controller);
		}
	}
	
	Super::Initialize(Character);
}

bool UUserdefinedPlayerStateBase::IsValidValues() const
{
	if (Super::IsValidValues() && MyPlayerController) return true;

	if (!MyPlayerController)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyPlayerController Invalid State"), *GetFullName());

	return false;
}

void UUserdefinedPlayerStateBase::InputKey(EPlayerInputType Type, bool bValue)
{
	if (IsValidValues()) OnInputKey(Type, bValue);
}

void UUserdefinedPlayerStateBase::ChangeCharacterState(UDataTable* EnumTable, FName State)
{
	if (!IsValidValues()) return;

	MyCharacter->ChangeState(State);
}
