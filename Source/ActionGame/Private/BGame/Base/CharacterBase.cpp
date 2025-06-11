// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/CharacterBase.h"

#include "BGame/Base/ActionManagerComponent.h"
#include "BGame/Base/StateManagerComponent.h"
#include "BGame/Utility/CustomEnumRow.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));
	ActionManager = CreateDefaultSubobject<UActionManagerComponent>(TEXT("ActionManager"));

	TestFunc("Initialize");
}

void ACharacterBase::PostInitProperties()
{
	Super::PostInitProperties();

	if (StateList)
	{
		for (auto Element : StateList->GetRowMap())
		{
			auto Row = Element.Key;

			if (!StateNames.Contains(Row)) StateNames.Add(Row);

			UE_LOG(LogTemp, Warning, TEXT("Add StateNames %s"), *Row.ToString());
		}
	}
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ACharacterBase::ChangeState(const FName& NextState) const
{
	if (OnEnterState.IsBound()) OnEnterState.Broadcast(NextState);
	
	if (OnStateChanged.IsBound()) OnStateChanged.Broadcast(NextState);
	
	if (OnExitState.IsBound()) OnExitState.Broadcast(NextState);
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

