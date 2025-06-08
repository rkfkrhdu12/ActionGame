// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/AnimInstanceBase.h"

#include "BGame/Base/CharacterBase.h"
#include "BGame/Utility/CustomEnumHelper.h"
#include "BGame/Utility/CustomEnumTable.h"

UAnimInstanceBase::UAnimInstanceBase()
{
}

void UAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MyCharacter = Cast<ACharacterBase>(TryGetPawnOwner());
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

	if (StateEnum->IsValidLowLevelFast())
	{
		UE_LOG(LogTemp, Error, TEXT("%s : StateEnum(현재 사용할 상태 열거형)이 설정 되어 있지 않습니다."), *GetName());
		UE_LOG(LogTemp, Error, TEXT("%s : StateEnum(현재 사용할 상태 열거형) is Not Set."), *GetName());
	}
	
	int32 index = -1;
	for (FString& EnumName : UCustomEnumHelper::GetEnumNames(StateEnum->GetListName()))
	{
		CurrentStateIndexList.Add(EnumName, ++index);

		UE_LOG(LogTemp, Warning, TEXT("Add List: %s"), *EnumName);
	}
}
