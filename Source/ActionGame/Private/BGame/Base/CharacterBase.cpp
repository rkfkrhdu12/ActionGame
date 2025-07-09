// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/CharacterBase.h"

#include "BGame/Base/ActionManagerComponent.h"
#include "BGame/Base/KnockbackComponent.h"
#include "BGame/Base/StateEventHandle.h"
#include "BGame/Base/StateManagerComponent.h"
#include "BGame/Base/UserdefinedState.h"
#include "Kismet/KismetMathLibrary.h"

#define AssignDefaultSubobject(Variable)\
	Variable = CreateDefaultSubobject<std::remove_reference_t<decltype(*Variable)>>(#Variable)

// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AssignDefaultSubobject(StateEventHandle);
	AssignDefaultSubobject(KnockbackComp);
	
	PrintErrorCheckLog("Initialize");
}

void ACharacterBase::PostInitProperties()
{
	Super::PostInitProperties();
	
	PrintErrorCheckLog("PostInitProperties");
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	PrintErrorCheckLog("BeginPlay");
}

void ACharacterBase::Move(const FVector2D& MoveDirection)
{
	auto MyController = GetController();
	if (!MyController) return;

	auto ControlledRotate = MyController->GetControlRotation();

	auto ForwardDirection = UKismetMathLibrary::GetForwardVector(ControlledRotate);
	auto RightDirection = UKismetMathLibrary::GetRightVector(ControlledRotate);

	AddMovementInput(ForwardDirection, MoveDirection.X, false);
	AddMovementInput(RightDirection, MoveDirection.Y, false);
}

void ACharacterBase::ChangeState(const FName& NextState) const
{
	if (StateManagerComp) StateManagerComp->ChangeState(NextState);
}

void ACharacterBase::OnKnockback(const FVector& TargetLocation, float Power)
{
	if (KnockbackComp) KnockbackComp->OnStart(TargetLocation, Power);
}

void ACharacterBase::LineTrace(FVector StartLocation, FVector EndLocation, FHitResult& OutHitResult)
{
	if (auto World = GetWorld())
	{
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		
		bool bHit = World->LineTraceSingleByChannel(
			OutHitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility,
			Params);

		if (bIsDrawDebugLine) DrawDebugLine(World, StartLocation, EndLocation, bHit ? FColor::Red : FColor::Green, false, 0.1f);
	}
}

void ACharacterBase::ChangeState(ACharacterBase* Target, UDataTable* EnumTable, FName State)
{
	if (!EnumTable || !Target) return;

	Target->ChangeState(State);
}






bool ACharacterBase::IsCompareTableData(UDataTable* DataTable, FName RowData, FName CompareName)
{
	return RowData == CompareName;
}
int32 ACharacterBase::GetStateIndex(const FName& StateName) const
{
	return StateNames.Find(StateName);
}

TArray<class UUserdefinedState*> ACharacterBase::GetStateClassList() const
{
	return StateList;
}

TArray<FName> ACharacterBase::GetStateNames() const
{
	return StateNames; 
}

FName ACharacterBase::GetCurrentStateName() const
{
	if (StateManagerComp) return StateManagerComp->GetCurrentStateName();

	return FName();
}

