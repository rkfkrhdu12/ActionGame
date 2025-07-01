// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/Monster/AIControllerBase.h"

#include "BGame/Base/Player/PlayerCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Slate/SGameLayerManager.h"

AAIControllerBase::AAIControllerBase()
{
}

void AAIControllerBase::FindPlayer()
{
	if (!MyPlayerCharacter) return;

	if (OnFindPlayer.IsBound()) OnFindPlayer.Broadcast(true);
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (!MyPlayerCharacter)
	if (auto GameStaticPlayerCharacter = Cast<APlayerCharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		MyPlayerCharacter = GameStaticPlayerCharacter;
	}
}

void AAIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
	if (OnMoveFinished.IsBound()) OnMoveFinished.Broadcast(true);
}

EPathFollowingStatus::Type AAIControllerBase::GetCharacterStatus() const
{
	if (!GetPathFollowingComponent()) return EPathFollowingStatus::Type::Paused;
	
	return GetPathFollowingComponent()->GetStatus();
}
