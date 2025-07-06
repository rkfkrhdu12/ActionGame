// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/UserdefinedState.h"

#include "BGame/Base/CharacterBase.h"

void UUserdefinedState::Initialize(ACharacterBase* Character)
{
	if (!Character) return;

	MyCharacter = Character;
	if (MyCharacter)
	{
		MyController = MyCharacter->GetController();
		MyMesh = MyCharacter->GetMesh();

		bIsInitialized = true;

		Awake();
	}
}

void UUserdefinedState::Awake()
{
	BeginPlay();
}

void UUserdefinedState::Enable()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Start"), *GetName());

	bIsEnabled = true;

	if (IsValidValues()) OnEnable();
}

void UUserdefinedState::Disable()
{
	// UE_LOG(LogTemp, Warning, TEXT("%s : End"), *GetName());
	if (IsValidValues()) OnDisable();

	bIsEnabled = false;
}

void UUserdefinedState::Update(float DeltaTime)
{
	if (IsValidValues()) Tick(DeltaTime);
}

void UUserdefinedState::AnimNotify(const UDataTable* DataTablePtr,
                                   FName SelectedRowName,
                                   const FAnimNotifyEventReference& EventReference)
{
	if (IsValidValues()) OnAnimNotify(DataTablePtr, SelectedRowName, EventReference);
}


bool UUserdefinedState::CanChanged_Implementation(const FName& NextState)
{
	return true;
}

void UUserdefinedState::StartDelay(float DelayTime, FTimerHandle& TimerHandle, bool bIsLoop)
{
	if (!IsValidValues()) return;

	if (auto World = MyCharacter->GetWorld())
	{
		World->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&UUserdefinedState::DelayFinished,
			DelayTime,
			bIsLoop);

		if (TimerHandle.IsValid())
		{
			if (!bIsLoop)	{ if (DelayTimers.Find(TimerHandle) == INDEX_NONE) DelayTimers.Add(TimerHandle); }
			else			{ if (DelayLoopTimers.Find(TimerHandle) == INDEX_NONE) DelayLoopTimers.Add(TimerHandle); }
		}
	}
}

void UUserdefinedState::DelayFinished()
{
	OnDelayFinished();
}

void UUserdefinedState::ClearTimer(FTimerHandle TimerHandle)
{
	if (!TimerHandle.IsValid()) return;

	if (DelayTimers.Find(TimerHandle) != INDEX_NONE) DelayTimers.Remove(TimerHandle);
	if (DelayLoopTimers.Find(TimerHandle) != INDEX_NONE) DelayLoopTimers.Remove(TimerHandle);

	if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

bool UUserdefinedState::IsValidValues() const
{
	if (MyCharacter && MyController && MyMesh && bIsEnabled) return true;

	if (!MyCharacter)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyCharacter Invalid State"), *GetFullName());
	if (!MyController)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyController Invalid State"), *GetFullName());
	if (!MyMesh)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyMesh Invalid State"), *GetFullName());

	return false;
}

float UUserdefinedState::GetRemainTimerTime(FTimerHandle TimerHandle)
{
	if (IsValidValues())
	{
		if (auto World = MyCharacter->GetWorld())
		{
			return World->GetTimerManager().GetTimerRemaining(TimerHandle);
		}
	}

	return -1.f;
}

bool UUserdefinedState::IsValidTimer(FTimerHandle TimerHandle)
{
	if (!IsValidValues()) return false;

	UE_LOG(LogTemp, Warning, TEXT("IsValidTimer : Start"));
	
	bool returnValue = false;
	if (GetRemainTimerTime(TimerHandle) <= 0.f && GetRemainTimerTime(TimerHandle) > -0.1f
		&& GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		UE_LOG(LogTemp, Warning, TEXT("IsValidTimer : Compare"));
		if (DelayTimers.Find(TimerHandle) != INDEX_NONE)
		{
		UE_LOG(LogTemp, Warning, TEXT("IsValidTimer : is DelayTimers"));
			returnValue = true;
			DelayTimers.Remove(TimerHandle);
		}

		if (DelayLoopTimers.Find(TimerHandle) != INDEX_NONE)
		{
		UE_LOG(LogTemp, Warning, TEXT("IsValidTimer : is DelayLoopTimers"));
			returnValue = true;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("IsValidTimer : %d"), returnValue);
	
	return returnValue;
}

FVector UUserdefinedState::GetActorLocation() const
{
	if (!IsValidValues()) return FVector::OneVector;

	return MyCharacter->GetActorLocation();
}
