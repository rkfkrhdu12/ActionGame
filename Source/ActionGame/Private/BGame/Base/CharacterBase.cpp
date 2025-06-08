// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/CharacterBase.h"

#include "BGame/Base/ActionManagerComponent.h"
#include "BGame/Base/StateManagerComponent.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));
	ActionManager = CreateDefaultSubobject<UActionManagerComponent>(TEXT("ActionManager"));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	StateManager = FindComponentByClass<UStateManagerComponent>();
}


void ACharacterBase::ChangeState(const FString& NextState) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s ChangeState %s"),*GetName(), *StateManager->GetName());

	if (StateManager) { StateManager->ChangeState(NextState); }
}

