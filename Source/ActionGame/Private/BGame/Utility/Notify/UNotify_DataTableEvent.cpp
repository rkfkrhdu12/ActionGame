// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Utility/Notify/UNotify_DataTableEvent.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/StateEventHandle.h"

void UUNotify_DataTableEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ACharacterBase* MyCharacter = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		if (auto hStateEvent = MyCharacter->GetStateEventHandle())
		{
			if (hStateEvent->OnAnimNotify.IsBound())
			{
				hStateEvent->OnAnimNotify.Broadcast(NotifyTableHandle.DataTable,
				                                    NotifyTableHandle.RowName, EventReference);
			}
		}
	}
}

FString UUNotify_DataTableEvent::GetNotifyName_Implementation() const
{
	if (NotifyTableHandle.IsNull()) return Super::GetNotifyName_Implementation();

	return NotifyTableHandle.RowName.ToString();
}