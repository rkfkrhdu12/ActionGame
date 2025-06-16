// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Player/UserdefinedPlayerStateBase.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/Player/PlayerControllerBase.h"

void UUserdefinedPlayerStateBase::Initialize(ACharacterBase* Character)
{
	if (!Character) return;
	
	MyCharacter = Character;
	if (MyCharacter)
	{
		MyPlayerController = Cast<APlayerControllerBase>(MyCharacter->GetController());
	}
	
	Super::Initialize(Character);
}
