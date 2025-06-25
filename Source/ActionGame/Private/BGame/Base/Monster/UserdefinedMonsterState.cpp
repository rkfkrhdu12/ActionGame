// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Monster/UserdefinedMonsterState.h"

#include "BGame/Base/Monster/MonsterCharacterBase.h"
#include "Runtime/AIModule/Classes/AIController.h"

void UUserdefinedMonsterState::Initialize(ACharacterBase* Character)
{
	if (!Character) return;
	
	MyCharacter = Character;

	MyMonsterCharacter = Cast<AMonsterCharacterBase>(Character);
	if (MyMonsterCharacter)
	{
		if (auto Controller = MyMonsterCharacter->GetController<AAIController>())
		{
			// MyAIController = Cast<AAIController>(Controller);
		}
	}
	
	Super::Initialize(Character);
}

bool UUserdefinedMonsterState::IsValidValues() const
{
	if (Super::IsValidValues() && MyMonsterCharacter && MyAIController) return true;
	
	if (!MyMonsterCharacter)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyMonsterCharacter Invalid State"), *GetFullName());
	if (!MyAIController)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyAIController Invalid State"), *GetFullName());

	return false;
}
