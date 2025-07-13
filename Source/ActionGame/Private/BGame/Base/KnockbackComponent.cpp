// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/KnockbackComponent.h"

#include "BGame/Base/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UKnockbackComponent::UKnockbackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MyCharacter = Cast<ACharacterBase>(GetOwner());
	if (MyCharacter)
	{
		MyCharacterMovement = MyCharacter->GetCharacterMovement();
		if (MyCharacterMovement)
		{
			BaseGravityScale = MyCharacterMovement->GravityScale;
			BaseGroundFriction = MyCharacterMovement->GroundFriction;
			BaseBrakingValue = MyCharacterMovement->BrakingDecelerationWalking;
			BaseWalkSpeed = MyCharacterMovement->MaxWalkSpeed;
		}
		
		if (auto Controller = MyCharacter->GetController())
		{
			MyController = Controller;
		}
	}
}

void UKnockbackComponent::OnStart(const FVector& ReceiveLocation, float Power)
{
	if (!MyCharacter || !MyCharacterMovement) return;

	TargetLocation = ReceiveLocation;
	
	MyCharacterMovement->StopMovementImmediately();

	MyCharacterMovement->GroundFriction = 0.0f;
	MyCharacterMovement->BrakingDecelerationWalking = 1400.0f;
	MyCharacterMovement->MaxWalkSpeed = 0.0f;

	FVector ActorLocation = MyCharacter->GetActorLocation();
	ActorLocation.Z = 0;
	TargetLocation.Z = 0;
	
	auto lookAtRotate = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);
	MyCharacter->SetActorRotation(lookAtRotate);
	
	FVector knockbackDirection = MyCharacter->GetActorForwardVector() * -1.0f;
	knockbackDirection.Normalize();

	DrawDebugLine(GetWorld(), MyCharacter->GetActorLocation(), ReceiveLocation, true ? FColor::Red : FColor::Green,
		false, 1.f);
	
	MyCharacterMovement->AddImpulse(knockbackDirection * Power, true);

	KnockbackTime = 0.0f;
	bIsEnable = true;

	UE_LOG(LogTemp, Log, TEXT("%s Knockback Start "), *MyCharacter->GetName());
}

void UKnockbackComponent::OnEnd()
{
	if (!bIsEnable)  return;
	if (MyCharacter == nullptr || MyCharacterMovement == nullptr) return;

	MyCharacterMovement->GravityScale = BaseGravityScale;
	MyCharacterMovement->GroundFriction = BaseGroundFriction;
	MyCharacterMovement->BrakingDecelerationWalking = BaseBrakingValue;
	MyCharacterMovement->MaxWalkSpeed = BaseWalkSpeed;

	if (MyController != nullptr)
		MyController->SetIgnoreMoveInput(false);

	UE_LOG(LogTemp, Log, TEXT("%s Knockback End "), *MyCharacter->GetName());
	bIsEnable = false;
}

// Called every frame
void UKnockbackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!bIsEnable) return;

	if (MyCharacter == nullptr || MyCharacterMovement == nullptr) return;

	KnockbackTime += DeltaTime;
	
	// if (!TargetLocation.IsNearlyZero())
	// {
	// 	FRotator characterRotate = MyCharacter->GetActorRotation();
	// 	FRotator lookAtRotate = UKismetMathLibrary::FindLookAtRotation(MyCharacter->GetActorLocation(), TargetLocation);
	// 	FRotator resultRotate = UKismetMathLibrary::RInterpTo(characterRotate, lookAtRotate, DeltaTime, 10.f);
	//
	// 	resultRotate.Pitch = characterRotate.Pitch;
	// 	resultRotate.Roll = characterRotate.Roll;
	//
	// 	MyCharacter->SetActorRotation(resultRotate);
	// 	
	// 	UE_LOG(LogTemp, Log, TEXT("%s Knockback Ing "), *MyCharacter->GetName());
	// }

	if (KnockbackTime >= .15f && MyCharacterMovement->Velocity.Size() <= 35.f)
		OnEnd();
}

