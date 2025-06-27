// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/StateManagerComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/StateEventHandle.h"
#include "BGame/Base/UserdefinedState.h"
#include "BGame/Base/Player/PlayerControllerBase.h"

UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1;
}

void UStateManagerComponent::ChangeState(const FName& NextState)
{
	if (!MyCharacter) return;
	
	auto StateEventHandle = MyCharacter->GetStateEventHandle();
	if (!StateEventHandle) return;

	StateEventHandle->BroadcastStateChanged(NextState);
	
	StateEventHandle->BroadcastPreStateChanged(CurrentEnableStateName, NextState);

	if (CurrentEnableStateName == NextState) return;

	auto List = MyCharacter->GetStateClassList();
	auto CurrentIndex = MyCharacter->GetStateIndex(CurrentEnableStateName);
	auto NextIndex = MyCharacter->GetStateIndex(NextState);

	bool ChangeSuccess = true;
	if (CurrentIndex != INDEX_NONE && CurrentIndex < List.Num())
	{
		if (List.Num() > CurrentIndex)
		{
			ChangeSuccess = List[CurrentIndex]->CanChanged(NextState);
			if (ChangeSuccess)
			{
				StateEventHandle->BroadcastExitState(CurrentEnableStateName);
				
				CurrentState->Disable();
			}
		}
	}

	if (NextIndex != INDEX_NONE && ChangeSuccess && NextIndex < List.Num())
	{
		CurrentState = List[NextIndex];
		CurrentEnableStateName = NextState;
		StateEventHandle->BroadcastEnterState(CurrentEnableStateName);

		CurrentState->Enable();
	}

	StateEventHandle->BroadcastPostStateChanged(CurrentEnableStateName, NextState);
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
		if (auto hStateEvent = MyCharacter->GetStateEventHandle())
			if (!hStateEvent->OnAnimNotify.IsBoundToObject(this))
				hStateEvent->OnAnimNotify.AddUObject(this, &UStateManagerComponent::AnimNotify);

		if (auto StateList = MyCharacter->StateNameList)
		{
			for (auto Element : StateList->GetRowMap())
			{
				auto Row = Element.Key;
				if (!MyCharacter->StateNames.Contains(Row)) MyCharacter->StateNames.Add(Row);
			}
		}
		
		auto List = MyCharacter->States;
		if (List.Num() != 0)
		{
			for (auto Element : List)
				Element->Initialize(MyCharacter);
		}

		ChangeState(DefaultResetStateName);
	}
}

void UStateManagerComponent::PostInitProperties()
{
	Super::PostInitProperties();

	
}

void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState) CurrentState->Tick(DeltaTime);
}

void UStateManagerComponent::SetTickInterval(float Interval)
{
	PrimaryComponentTick.TickInterval = Interval;
}
