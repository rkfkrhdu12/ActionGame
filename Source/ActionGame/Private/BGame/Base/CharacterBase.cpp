// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/CharacterBase.h"

#include "BGame/Base/ActionManagerComponent.h"
#include "BGame/Base/StateManagerComponent.h"
#include "BGame/Base/UserdefinedState.h"

#define AssignDefaultSubobject(Variable)\
	Variable = CreateDefaultSubobject<std::remove_reference_t<decltype(*Variable)>>(#Variable)

// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// AssignDefaultSubobject(StateManager);
	AssignDefaultSubobject(ActionManager);
	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));

	TestFunc("Initialize");
}

void ACharacterBase::PostInitProperties()
{
	Super::PostInitProperties();
	if (HasAnyFlags(RF_ClassDefaultObject)) return;
	
	if (StateList)
	{
		for (auto Element : StateList->GetRowMap())
		{
			auto Row = Element.Key;
			if (!StateNames.Contains(Row)) StateNames.Add(Row);
		}
	}
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (HasAnyFlags(RF_ClassDefaultObject)) return;
	
	if (StateClassList.Num() != 0)
	{
		for (auto Element : StateClassList)
			Element->Initialize(this);
	}
	

	StateManager = FindComponentByClass<UStateManagerComponent>();
}

void ACharacterBase::ChangeState(const FName& NextState) const
{
	if (OnStateChanged.IsBound()) OnStateChanged.Broadcast(NextState);

	if (StateManager) StateManager->ChangeState(NextState);
}

void ACharacterBase::ChangeState(ACharacterBase* Target, UDataTable* EnumTable, FName State)
{
	if (!EnumTable || !Target) return;

	Target->ChangeState(State);
}

auto ACharacterBase::GetStateIndex(const FName& StateName) const -> int32
{
	return StateNames.Find(StateName);
}

