// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Utility/UserdefinedMontageNotify.h"

void UUserdefinedMontageNotify::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotify(BranchingPointPayload);
}

FString UUserdefinedMontageNotify::GetNotifyName_Implementation() const
{
	if (NotifyName.IsNone() || !NotifyName.IsValid())
		return Super::GetNotifyName_Implementation();

	return Super::GetNotifyName_Implementation();
}
