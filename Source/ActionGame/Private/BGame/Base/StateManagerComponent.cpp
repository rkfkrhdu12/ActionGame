// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/StateManagerComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/UserdefinedState.h"
#include "BGame/Base/Player/PlayerControllerBase.h"

UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateManagerComponent::ChangeState(const FName& NextState)
{
	if (!MyCharacter) return;

	if (MyCharacter->OnPreStateChanged.IsBound())
		MyCharacter->OnPreStateChanged.Broadcast(CurrentEnableStateName, NextState);

	if (CurrentEnableStateName == NextState) return;

	auto List = MyCharacter->GetStateClassList();
	auto CurrentIndex = MyCharacter->GetStateIndex(CurrentEnableStateName);
	auto NextIndex = MyCharacter->GetStateIndex(NextState);

	bool ChangeSuccess = true;
	if (CurrentIndex != INDEX_NONE)
	{
		if (List.Num() > CurrentIndex)
		{
			ChangeSuccess = List[CurrentIndex]->CanChanged(NextState);
			if (ChangeSuccess)
			{
				if (MyCharacter->OnExitState.IsBound())
					MyCharacter->OnExitState.Broadcast(CurrentEnableStateName);
				
				CurrentState->Disable();
			}
		}
	}

	if (NextIndex != INDEX_NONE && ChangeSuccess)
	{
		CurrentState = List[NextIndex];
		CurrentEnableStateName = NextState;
		if (MyCharacter->OnEnterState.IsBound())  MyCharacter->OnEnterState.Broadcast(NextState);

		CurrentState->Enable();
	}
	
	if (MyCharacter->OnPostStateChanged.IsBound())
		MyCharacter->OnPostStateChanged.Broadcast(CurrentEnableStateName, NextState);
}

void UStateManagerComponent::AnimNotify(const UDataTable* DataTablePtr, FName SelectedRowName,
	const FAnimNotifyEventReference& EventReference) const
{
	if (CurrentState) CurrentState->AnimNotify(DataTablePtr, SelectedRowName, EventReference);
}


void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<ACharacterBase>(GetOwner());
	if (MyCharacter)
	{
		MyCharacter->OnAnimNotify.AddUObject(this, &UStateManagerComponent::AnimNotify);
		
		UE_LOG(LogTemp, Display, TEXT("%s BeginPlay %s"), *MyCharacter->GetName(), *GetFullName());
	
		auto List = MyCharacter->GetStateClassList();
		if (List.Num() != 0)
		{
			for (auto Element : List)
				Element->Initialize(MyCharacter);
		}

		ChangeState("Idle");
		
	}
}
