// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/StateManagerComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/UserdefinedState.h"
#include "BGame/Base/Player/InputManagerComponent.h"
#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "BGame/Base/Player/PlayerControllerBase.h"


UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateManagerComponent::ChangeState(const FName& NextState)
{
	if (!MyCharacter) return;

	
	if (MyCharacter->OnPreStateChanged.IsBound()) MyCharacter->OnPreStateChanged.Broadcast(CurrentState, NextState);



	
	if (MyCharacter->OnPostStateChanged.IsBound()) MyCharacter->OnPostStateChanged.Broadcast(CurrentState, NextState);
}

//
// void UStateManagerComponent::ChangeState(const FString& NextState)
// {
// 	// nUE_LOG(LogTemp, Warning, TEXT("%s ChangeState %s"), *GetFullName(), *NextState);
//
// 	if (CurrentStateName == NextState) return;
//
// 	if (MyCharacter)
// 	if (auto UseStateEnum = MyCharacter->GetUseStateEnum())
// 	{
// 		if (!UseStateEnum->GetStateList().Contains(NextState)) return;
// 	
// 		auto StateList = UseStateEnum->GetStateList();
// 		if (auto ChangedState = StateList[NextState])
// 		{
// 			if (StateList.Contains(CurrentStateName))
// 			{
// 				PrevStateName = CurrentStateName;
//
// 				StateList[CurrentStateName]->Disable();
// 			}
//
// 			CurrentStateName = NextState;
// 			
// 			StateList[CurrentStateName]->Enable();
// 		}
// 	}
// }
//
// void UStateManagerComponent::BeginPlay()
// {
// 	Super::BeginPlay();
// 	InitializeComponents();
//
// 	if (auto UseStateEnum = MyCharacter->GetUseStateEnum())
// 	{
// 		auto StateList = UseStateEnum->GetStateList();
//
// 		TArray<UUserdefinedState*> ClassList;
// 		StateList.GenerateValueArray(ClassList);
// 		int32 Index = -1;
// 		for (auto State : ClassList)
// 		{
// 			if (State) State->Initialize(MyCharacter, ++Index);
// 		}
//
// 		if (MyCharacter)
// 		{
// 			if (!MyCharacter->OnInputAttack.IsAlreadyBound(this, &UStateManagerComponent::InputAttack))
// 				MyCharacter->OnInputAttack.AddDynamic(this, &UStateManagerComponent::InputAttack);
//
// 			if (!MyCharacter->OnStateChanged.IsAlreadyBound(this, &UStateManagerComponent::ChangeState))
// 				MyCharacter->OnStateChanged.AddDynamic(this, &UStateManagerComponent::ChangeState);
// 		}
//
// 		ChangeState("Idle");
// 	}
// }
//
// void UStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
// 	FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// if (CurrentState) CurrentState->Update(DeltaTime);
// }
//
void UStateManagerComponent::InitializeComponents()
{
	if (GetOwner() != nullptr)
	{
		MyCharacter = Cast<APlayerCharacterBase>(GetOwner());
		if (MyCharacter != nullptr)
		{
			MyController = Cast<APlayerControllerBase>(MyCharacter->GetController());
		}
	}
}
//
// class UUserdefinedState* UStateManagerComponent::GetCurrentState() const
// {
// 	if (MyCharacter)
// 		if (MyCharacter->GetUseStateEnum())
// 			return *MyCharacter->GetUseStateEnum()->GetStateList().Find(CurrentStateName);
//
// 	return nullptr;
// }
//
// FString UStateManagerComponent::GetCurrentStateName() const
// {
// 	// if (CurrentState) return CurrentState->GetCurrentStateName();
// 	// else
// 		return "";
// }
//
// int32 UStateManagerComponent::GetCurrentStateIndex() const
// {
// 	// if (CurrentState) return CurrentState->GetCurrentStateIndex();
// 	// else
// 		return 0;
// }
