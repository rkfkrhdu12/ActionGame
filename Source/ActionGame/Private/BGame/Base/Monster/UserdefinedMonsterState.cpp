// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Monster/UserdefinedMonsterState.h"

#include "NavigationSystem.h"
#include "BGame/Base/Monster/AIControllerBase.h"
#include "BGame/Base/Monster/MonsterCharacterBase.h"
#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/AIModule/Classes/AIController.h"

void UUserdefinedMonsterState::OnMoveRandomPointInRadius(FVector OriginLocation, float Radius, FVector& DestLocation)
{
	if (!IsValidValues()) return;

	FNavLocation RandomNavLocation;
	if (auto NavSystem = UNavigationSystemV1::GetCurrent(MyCharacter->GetWorld()))
	{
		if (NavSystem->GetRandomReachablePointInRadius(OriginLocation, Radius, RandomNavLocation))
		{
			DestLocation = RandomNavLocation.Location;
			MyAIController->MoveToLocation(DestLocation);
		}
	}
}

void UUserdefinedMonsterState::OnMoveToLocation(FVector Destination)
{
	if (!IsValidValues()) return;

	MyAIController->MoveToLocation(Destination);
}

void UUserdefinedMonsterState::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	if (bIsLookAtPlayer) LookAtPlayerCharacter();
}

void UUserdefinedMonsterState::Initialize(ACharacterBase* Character)
{
	if (!Character) return;

	MyCharacter = Character;

	MyMonsterCharacter = Cast<AMonsterCharacterBase>(Character);
	if (MyMonsterCharacter)
	{
		if (auto Controller = MyMonsterCharacter->GetController<AAIController>())
		{
			MyAIController = Cast<AAIControllerBase>(Controller);
			if (MyAIController)
			{
				MyPlayerCharacter = MyAIController->GetPlayerCharacter();
				if (!MyAIController->OnMoveFinished.IsAlreadyBound(this, &UUserdefinedMonsterState::OnMoveFinished))
					MyAIController->OnMoveFinished.AddDynamic(this, &UUserdefinedMonsterState::OnMoveFinished);
			}
		}

		DefaultWalkSpeed = MyMonsterCharacter->GetCharacterMovement()->MaxWalkSpeed;
	}

	Super::Initialize(Character);

	if (MyMesh)
	{
		if (auto animInst = MyMesh->GetAnimInstance())
		{
			animInst->OnPlayMontageNotifyBegin.AddDynamic(this, &UUserdefinedMonsterState::ApplyDamageToPlayer);
		}
	}
}

bool UUserdefinedMonsterState::IsValidValues() const
{
	if (Super::IsValidValues() &&
		MyMonsterCharacter && MyAIController && MyPlayerCharacter /* && MyPathFollowingComponent */)
		return true;

	if (!MyMonsterCharacter)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyMonsterCharacter Invalid State"), *GetFullName());
	if (!MyAIController)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyAIController Invalid State"), *GetFullName());
	if (!MyPlayerCharacter)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyPlayerCharacter Invalid State"), *GetFullName());

	return false;
}

void UUserdefinedMonsterState::MoveFinished(bool bIsSuccessful)
{
	if (IsValidValues()) OnMoveFinished(bIsSuccessful);
}

void UUserdefinedMonsterState::LookAtPlayerCharacter() const
{
	if (!IsValidValues()) return;

	auto LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetPlayerLocation());
	auto LerpRotation = UKismetMathLibrary::RLerp(MyCharacter->GetActorRotation(), LookAtRotation, .3f, true);
	if (abs(MyCharacter->GetActorRotation().Yaw - LookAtRotation.Yaw) > 0.1f)
	{
		MyCharacter->SetActorRotation(LerpRotation);
	}
}

void UUserdefinedMonsterState::ApplyDamageToPlayer(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (IsValidValues()) OnApplyDamageToPlayer(NotifyName); 
}


FVector UUserdefinedMonsterState::GetPlayerLocation() const
{
	if (!IsValidValues()) return FVector::ZeroVector;

	return MyPlayerCharacter->GetActorLocation();
}

float UUserdefinedMonsterState::GetDistanceToPlayer() const
{
	if (!IsValidValues()) return -1.f;

	return FVector::Distance(MyCharacter->GetActorLocation(), GetPlayerLocation());
	
}
