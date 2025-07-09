// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnockbackComponent.generated.h"


class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UKnockbackComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UKnockbackComponent();

	UFUNCTION(BlueprintCallable)
	void OnStart(const FVector& ReceiveLocation, float Power);

	void OnEnd();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	class ACharacterBase* MyCharacter = nullptr;
	UPROPERTY(EditAnywhere)
	UCharacterMovementComponent* MyCharacterMovement = nullptr;

	UPROPERTY(EditAnywhere)
	class AController* MyController = nullptr;

	FVector TargetLocation = FVector::ZeroVector;
	
	bool bIsEnable = false;
	float KnockbackTime = 0.f;
	
	float BaseGravityScale;
	float BaseGroundFriction;
	float BaseBrakingValue;
	float BaseWalkSpeed;
};
