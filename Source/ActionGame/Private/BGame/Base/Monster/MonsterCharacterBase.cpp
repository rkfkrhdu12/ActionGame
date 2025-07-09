// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Monster/MonsterCharacterBase.h"

#include "BGame/Base/Monster/MonsterStateManagerComponent.h"

#define AssignDefaultSubobject(Variable)\
Variable = CreateDefaultSubobject<std::remove_reference_t<decltype(*Variable)>>(#Variable)

AMonsterCharacterBase::AMonsterCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StateManagerComp = CreateDefaultSubobject<UMonsterStateManagerComponent>(TEXT("StateManager"));
	
	PrintErrorCheckLog("AMonsterCharacterBase Initialize");
}
