// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Monster/UserdefinedMonsterState.h"

#include "NavigationSystem.h"
#include "BGame/Base/Monster/AIControllerBase.h"
#include "BGame/Base/Monster/MonsterCharacterBase.h"
#include "BGame/Base/Player/PlayerCharacterBase.h"
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

void UUserdefinedMonsterState::LineTrace(FVector EndLocation, FHitResult& HitResult)
{
	if (!IsValidValues()) return;

	if (auto World = MyCharacter->GetWorld())
	{
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(MyCharacter);

		World->LineTraceSingleByChannel(
			HitResult,
			GetActorLocation(),
			EndLocation,
			ECC_Visibility,
			Params);
	}
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
				// MyPathFollowingComponent = MyAIController->GetPathFollowingComponent();
				if (!MyAIController->OnMoveFinished.IsAlreadyBound(this, &UUserdefinedMonsterState::OnMoveFinished))
					MyAIController->OnMoveFinished.AddDynamic(this, &UUserdefinedMonsterState::OnMoveFinished);
			}
		}
	}

	Super::Initialize(Character);
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
	//if (!MyPathFollowingComponent)
	//	UE_LOG(LogTemp, Warning, TEXT("%s : MyPathFollowingComponent Invalid State"), *GetFullName());

	return false;
}

void UUserdefinedMonsterState::MoveFinished(bool bIsSuccessful)
{
	if (IsValidValues()) OnMoveFinished(bIsSuccessful);
}


FVector UUserdefinedMonsterState::GetPlayerLocation() const
{
	if (!IsValidValues()) return FVector::OneVector;

	return MyPlayerCharacter->GetActorLocation();
}
