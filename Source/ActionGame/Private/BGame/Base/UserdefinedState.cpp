// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/UserdefinedState.h"

#include "BGame/Base/CharacterBase.h"

void UUserdefinedState::Initialize(ACharacterBase* Character)
{
	if (!Character) return;

	MyCharacter = Character;
	if (MyCharacter)
	{
		MyController = MyCharacter->GetController();
		MyMesh = MyCharacter->GetMesh();
	}
	
	bIsInitialized = true;

	Awake();
}

void UUserdefinedState::Awake()
{
	if (IsValidValues()) BeginPlay();
}

void UUserdefinedState::Enable()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Start"), *GetName());
	
	bIsEnabled = true;

	if (IsValidValues()) OnEnable();
}

void UUserdefinedState::Disable()
{
	// UE_LOG(LogTemp, Warning, TEXT("%s : End"), *GetName());

	bIsEnabled = false;
	
	if (IsValidValues()) OnDisable();
}

void UUserdefinedState::Update(float DeltaTime)
{
	if (IsValidValues()) Tick(DeltaTime);
}

void UUserdefinedState::AnimNotify(const UDataTable* DataTablePtr,
					FName SelectedRowName,
					const FAnimNotifyEventReference& EventReference)
{
	if (IsValidValues()) OnAnimNotify(DataTablePtr, SelectedRowName, EventReference);
}


bool UUserdefinedState::CanChanged_Implementation(const FName& NextState)
{
	return true;
}

bool UUserdefinedState::IsValidValues() const
{
	if (MyCharacter && MyController && MyMesh) return true;

	if (!MyCharacter)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyCharacter Invalid State"), *GetFullName());
	if (!MyController)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyController Invalid State"), *GetFullName());
	if (!MyMesh)
		UE_LOG(LogTemp, Warning, TEXT("%s : MyMesh Invalid State"), *GetFullName());
	
	return false;
}







//void UUserdefinedState::AnimStart(UAnimMontage* Montage)
//{
//	if (IsValidValues()) OnAnimStart(Montage);
//}
//
//void UUserdefinedState::AnimComplete(UAnimMontage* Montage, bool bInterrupted)
//{
//	if (bInterrupted)
//		if (IsValidValues()) AnimInterrupted();
//	else
//		if (IsValidValues()) OnAnimComplete(Montage, bInterrupted);
//}
//
//void UUserdefinedState::AnimBlendIn(UAnimMontage* Montage)
//{
//	if (IsValidValues()) OnAnimBlendIn(Montage);
//}
//
//void UUserdefinedState::AnimBlendOut(UAnimMontage* Montage, bool bInterrupted)
//{
//	if (bInterrupted)
//		if (IsValidValues()) AnimInterrupted();
//	else
//		if (IsValidValues()) OnAnimBlendOut(Montage, bInterrupted);
//}
//
//void UUserdefinedState::AnimInterrupted()
//{
//	if (IsValidValues()) OnAnimInterrupted();
//}
