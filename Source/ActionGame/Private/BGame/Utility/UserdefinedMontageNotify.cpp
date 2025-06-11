// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Utility/UserdefinedMontageNotify.h"


FString UUserdefinedMontageNotify::GetNotifyName_Implementation() const
{
	if (NotifyName.IsNone() || !NotifyName.IsValid())
		return Super::GetNotifyName_Implementation();

	return Super::GetNotifyName_Implementation();
}

void UUserdefinedMontageNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
}
