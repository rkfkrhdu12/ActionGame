// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/UserdefinedState.h"

#include "BGame/Base/AnimInstanceBase.h"
#include "BGame/Base/CharacterBase.h"

void UUserdefinedState::Initialize(ACharacterBase* Character)
{
	if (!Character) return;

	MyCharacter = Character;
	if (MyCharacter)
	{
		MyController = MyCharacter->GetController();
		MyMesh = MyCharacter->GetMesh();
		if (MyMesh)
		{
			MyAnimInstance = Cast<UAnimInstanceBase>(MyMesh->GetAnimInstance());
		}
	}

	bIsInitialized = true;
}

void UUserdefinedState::Awake()
{
	BeginPlay();
}

void UUserdefinedState::Enable()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Start"), *CurrentStateName);

	OnEnable();
}

void UUserdefinedState::Disable()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : End"), *CurrentStateName);

	OnDisable();
}

void UUserdefinedState::Update(float DeltaTime)
{
	Tick(DeltaTime);
}

void UUserdefinedState::AnimStart(UAnimMontage* Montage)
{
	OnAnimStart(Montage);
}

void UUserdefinedState::AnimComplete(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		AnimInterrupted();
		return;
	}
	else
	{
		OnAnimComplete(Montage, bInterrupted);
	}
}

void UUserdefinedState::AnimBlendIn(UAnimMontage* Montage)
{
	OnAnimBlendIn(Montage);
}

void UUserdefinedState::AnimBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted)
	{
		AnimInterrupted();
		return;
	}
	else
	{
		OnAnimBlendOut(Montage, bInterrupted);
	}
}

void UUserdefinedState::AnimInterrupted()
{
	OnAnimInterrupted();
}

bool UUserdefinedState::IsChangeState_Implementation(const FString& NextState)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s : IsChangeState"), *CurrentStateName);
	return true;
}

void UUserdefinedState::ChangeState(const FString& NextState)
{
	if (!MyCharacter) return;
	
	UE_LOG(LogTemp, Warning, TEXT("%s ChangeState "),*MyCharacter->GetName());

	MyCharacter->ChangeState(NextState);
}

bool UUserdefinedState::IsValidValues() const
{
	if (MyCharacter && MyController && MyMesh && MyAnimInstance) return true;

	UE_LOG(LogTemp, Warning, TEXT("%s : Invalid State"), *CurrentStateName);

	return false;
}
