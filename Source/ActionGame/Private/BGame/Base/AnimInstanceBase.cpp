// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/AnimInstanceBase.h"

#include "BGame/Base/CharacterBase.h"

UAnimInstanceBase::UAnimInstanceBase()
{
}

void UAnimInstanceBase::EnterState(const FName& StateName)
{
	if (MyCharacter)
	{
		auto index = MyCharacter->GetStateIndex(StateName);
		if (index > -1) CurrentStateIndex = index;
	}

	OnEnterStateEvent(StateName);
}

void UAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MyCharacter = Cast<ACharacterBase>(GetOwningActor());
	if (MyCharacter)
	{
		MyMesh = MyCharacter->GetMesh();
		
		if (auto hStateEvent = MyCharacter->GetStateEventHandle())
			if (!hStateEvent->OnEnterState.IsAlreadyBound(this, &UAnimInstanceBase::EnterState))
				hStateEvent->OnEnterState.AddDynamic(this, &UAnimInstanceBase::EnterState);
	}
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MyCharacter) return;

	MoveVelocity = MyCharacter->GetVelocity();
	MoveVelocity.Normalize();
	MoveSpeed = MyCharacter->GetVelocity().Length();

	float ForwardDot = MyCharacter->GetActorForwardVector().Dot(MoveVelocity);
	float RightDot = MyCharacter->GetActorRightVector().Dot(MoveVelocity);

	MoveDirection = FVector(ForwardDot, RightDot,0.f);
	MoveDirection.Normalize();
}

bool UAnimInstanceBase::IsEqualCurState(UDataTable* DataTable, FName RowData)
{
	return GetCurrentState() == RowData;
}

FName UAnimInstanceBase::GetCurrentState()
{
	if (States.Num() <= CurrentStateIndex)
		if (MyCharacter->GetStateNames().Num() != 0)
			States = MyCharacter->GetStateNames();
	
		if (States.Num() <= CurrentStateIndex)
			return FName();
	
	return States[CurrentStateIndex];
}

void UAnimInstanceBase::PostInitProperties()
{
	Super::PostInitProperties();
}
