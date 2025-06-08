// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/StateManagerComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/UserdefinedState.h"
#include "BGame/Base/Player/InputManagerComponent.h"
#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "BGame/Base/Player/PlayerControllerBase.h"
#include "BGame/Utility/CustomEnumTable.h"


UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateManagerComponent::ChangeState(const FString& NextState)
{
	UE_LOG(LogTemp, Warning, TEXT("%s ChangeState %s"),*GetOwner()->GetName(), *GetName());
	if (StateList.Num() <= 0 || UseStateEnum == nullptr) return;
	if (NextState.IsEmpty() || NextState == CurrentState->GetCurrentStateName()) return;
	
	FString OriginState = "";
	if (CurrentState != nullptr)
	{
		OriginState = CurrentState->GetCurrentStateName();
	
		if (CurrentState->IsChangeState(NextState))
		{
			PrevState = CurrentState;

			CurrentState->Disable();
		}
	}

	if (StateList[NextState] != nullptr)
	{
		CurrentState = StateList[NextState];
		CurrentState->Enable();
	}

	if (OnStateChanged.IsBound()) OnStateChanged.Broadcast(CurrentState->GetCurrentStateName(),
		OriginState, NextState);
}


void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeComponents();

	InitializeStateList();

	if (MyController)
	{
		auto InputManager = MyController->GetInputManagerComponent();
		if (!InputManager->OnInputAttack.IsAlreadyBound(this, &UStateManagerComponent::InputAttack))
			InputManager->OnInputAttack.AddDynamic(this, &UStateManagerComponent::InputAttack);
	}
}


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

void UStateManagerComponent::InitializeStateList()
{
	UE_LOG(LogTemp, Warning, TEXT("%s InitializeStateList 1   %d"),*GetOwner()->GetName(), StateList.Num());
	if (StateList.Num() <= 0 || UseStateEnum == nullptr) return;
	
	for (FString& EnumName : UseStateEnum->GetEnumNames())
	{
		if (StateList.Contains(EnumName))
		{
			if (UUserdefinedState* State = StateList[EnumName])
			{
				if (!State->IsInitialized()) State->Initialize(Cast<ACharacterBase>(GetOwner()));
				State->BeginPlay();
			}
		}
	}

	CurrentState = StateList["Idle"];
	CurrentState->Enable();
}




//////////////////////////////////////////////////////////////////////////
/// Only EDITOR
#if WITH_EDITOR
void UStateManagerComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (!GetOwner()) return;

	if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ValueSet) // Change  Value Set
	{
		if (PropertyChangedEvent.GetPropertyName().ToString() == "UseStateEnum")
		{
			if (UseStateEnum)
			{
				if (UseStateEnum->GetEnumNames().Num() != 0)
				{
					for (FString& EnumName : UseStateEnum->GetEnumNames())
					{
						if (!StateList.Contains(EnumName))
							StateList.Add(EnumName);
					}
				}
			}
			else
				UE_LOG(LogTemp, Error, TEXT("%s : UseStateEnum is Not Set !!"), *GetName());
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UStateManagerComponent::InputAttack(bool InputValue)
{
	if (InputValue)
	{
		ChangeState("Attack");
	}
}
#endif
