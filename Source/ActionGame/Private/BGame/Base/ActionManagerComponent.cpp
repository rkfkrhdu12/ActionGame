// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/ActionManagerComponent.h"

#include "BGame/Base/AnimInstanceBase.h"
#include "BGame/Base/CharacterBase.h"
#include "BGame/Base/StateManagerComponent.h"

// Sets default values for this component's properties
UActionManagerComponent::UActionManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionManagerComponent::BeginPlay()
{
	Super::BeginPlay();


	if (auto MyCharacter = Cast<ACharacterBase>(GetOwner()))
	{
		if (auto MyMesh = MyCharacter->GetMesh())
		{
			if (auto MyAnimInstance = Cast<UAnimInstanceBase>(MyMesh->GetAnimInstance()))
			{
				//if (!MyAnimInstance->OnMontageStarted.IsAlreadyBound(this,		&UActionManagerComponent::AnimMontageStarted))
				//	MyAnimInstance->OnMontageStarted.AddDynamic(this,			&UActionManagerComponent::AnimMontageStarted);
				//if (!MyAnimInstance->OnMontageEnded.IsAlreadyBound(this,		&UActionManagerComponent::AnimMontageEnded))
				//	MyAnimInstance->OnMontageEnded.AddDynamic(this,				&UActionManagerComponent::AnimMontageEnded);
				//if (!MyAnimInstance->OnMontageBlendedIn.IsAlreadyBound(this,	&UActionManagerComponent::AnimMontageBlendedIn))
				//	MyAnimInstance->OnMontageBlendedIn.AddDynamic(this,			&UActionManagerComponent::AnimMontageBlendedIn);
				//if (!MyAnimInstance->OnMontageBlendingOut.IsAlreadyBound(this,	&UActionManagerComponent::AnimMontageBlendedOut))
				//	MyAnimInstance->OnMontageBlendingOut.AddDynamic(this,		&UActionManagerComponent::AnimMontageBlendedOut);
				//if (!MyAnimInstance->OnPlayMontageNotifyBegin.IsAlreadyBound(this,	&UActionManagerComponent::AnimMontageNotifyBegin))
				//	MyAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this,		&UActionManagerComponent::AnimMontageNotifyBegin);
				//if (!MyAnimInstance->OnPlayMontageNotifyEnd.IsAlreadyBound(this,	&UActionManagerComponent::AnimMontageNotifyEnd))
				//	MyAnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this,		&UActionManagerComponent::AnimMontageNotifyEnd);
		
			}
		}
	}
}

// Called every frame
void UActionManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
