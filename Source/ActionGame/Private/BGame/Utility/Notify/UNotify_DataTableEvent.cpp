// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Utility/Notify/UNotify_DataTableEvent.h"

#include "BGame/Base/CharacterBase.h"

void UUNotify_DataTableEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ACharacterBase* MyCharacter = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		if (MyCharacter->OnAnimNotify.IsBound())
			MyCharacter->OnAnimNotify.Broadcast(NotifyTableHandle.DataTable,
				NotifyTableHandle.RowName, EventReference);
	}
}
