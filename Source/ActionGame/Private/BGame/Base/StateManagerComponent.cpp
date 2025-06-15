// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/StateManagerComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/UserdefinedState.h"

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

				List[CurrentIndex]->Disable();
			}
		}
	}

	if (NextIndex != INDEX_NONE && ChangeSuccess)
	{
		CurrentEnableStateName = NextState;
		if (MyCharacter->OnEnterState.IsBound())  MyCharacter->OnEnterState.Broadcast(NextState);

		List[NextIndex]->Enable();
	}
	
	if (MyCharacter->OnPostStateChanged.IsBound())
		MyCharacter->OnPostStateChanged.Broadcast(CurrentEnableStateName, NextState);

}

void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<ACharacterBase>(GetOwner());
	if (MyCharacter)
	{
		UE_LOG(LogTemp, Display, TEXT("%s BeginPlay %s"), *MyCharacter->GetName(), *GetFullName());
	
		// if (MyCharacter->OnStateChanged.IsAlreadyBound(this, &UStateManagerComponent::ChangeState))
		// 	MyCharacter->OnStateChanged.AddDynamic(this, &UStateManagerComponent::ChangeState);

		ChangeState("Idle");
	}
}
//
// void UStateManagerComponent::ChangeState(const FName& NextState)
// {
// 	if (!MyCharacter) return;
// 	if (CurrentState->GetCurrentStateName() == NextState) return;
// 	if (!StateClassMap.Contains(NextState)) return;
//
// 	// if (MyCharacter->OnPreStateChanged.IsBound()) MyCharacter->OnPreStateChanged.Broadcast(FName(CurrentState->GetCurrentStateName()), NextState);
//
// 	bool bSuccess = true;
// 	if (CurrentState)
// 	{
// 		bSuccess = CurrentState->IsChangeState(NextState);
// 		if (bSuccess)
// 		{
// 			CurrentState->Disable();
// 			if (MyCharacter->OnExitState.IsBound()) MyCharacter->OnExitState.Broadcast(FName(CurrentState->GetCurrentStateName()));
// 		}
// 	}
//
// 	if (bSuccess)
// 	{
// 		CurrentState = StateClassMap[NextState];
// 		CurrentState->Enable();
// 		
// 		if (MyCharacter->OnEnterState.IsBound()) MyCharacter->OnEnterState.Broadcast(FName(CurrentState->GetCurrentStateName()));
// 	}
// 	// if (MyCharacter->OnPostStateChanged.IsBound()) MyCharacter->OnPostStateChanged.Broadcast(FName(CurrentState->GetCurrentStateName()), NextState);
// }
//
// void UStateManagerComponent::InitializeState()
// {
// 	if (!DataTable || ClassList.Num() == 0) return;
//
// 	StateList = DataTable;
//
// 	for (UUserdefinedState* State : ClassList)
// 	{
// 		FName Name = FName(State->GetCurrentStateName());
// 		StateClassMap.Add(Name, State);
// 		StateClassList.Add(Name);
// 		
// 		State->Initialize(MyCharacter);
// 	}
//
// 	if (StateClassMap.Contains("Idle"))
// 	{
// 		CurrentState = StateClassMap["Idle"];
// 		CurrentState->Enable();
// 	}
// }
//
// void UStateManagerComponent::InitializeComponents()
// {
// 	if (GetOwner() != nullptr)
// 	{
// 		MyCharacter = Cast<APlayerCharacterBase>(GetOwner());
// 	}
// }

//
// int32 UStateManagerComponent::GetStateIndex(FName StateName) const
// {
// 	return StateClassList.Find(StateName);
// }
