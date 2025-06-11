// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Utility/Notify/UNotify_IDEvent.h"

#include "BGame/Base/ActionManagerComponent.h"

void UUNotify_IDEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (auto FindComp = MeshComp->GetOwner()->FindComponentByClass<UActionManagerComponent>())
	{ // Notify() Called After AnimMontageNotifyBegin() Call
		// UE_LOG(LogTemp, Warning, TEXT("UUNotify_IDEvent::Notify %d"), NotifyId);

		// FindComp->TestFuc();
	}
}
