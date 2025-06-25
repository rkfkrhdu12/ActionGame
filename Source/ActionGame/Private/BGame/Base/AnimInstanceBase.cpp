// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/AnimInstanceBase.h"

#include "BGame/Base/CharacterBase.h"

UAnimInstanceBase::UAnimInstanceBase()
{
}

void UAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MyCharacter = Cast<ACharacterBase>(GetOwningActor());
	if (MyCharacter)
	{
		MyMesh = MyCharacter->GetMesh();
		if (MyMesh)
		{
			MyMesh->GetAnimInstance()->Montage_SetEndDelegate(MontageEndDelegate);
			MyMesh->GetAnimInstance()->Montage_SetBlendedInDelegate(MontageBlendedInDelegate);
			MyMesh->GetAnimInstance()->Montage_SetBlendingOutDelegate(MontageBlendingOutDelegate);
		}
	}
}
