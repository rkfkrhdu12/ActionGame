// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/UserdefinedState.h"
#include "UserdefinedMonsterState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUserdefinedMonsterState : public UUserdefinedState
{
	GENERATED_BODY()
public:
	virtual void Initialize(ACharacterBase* Character) override;
	virtual bool IsValidValues() const override;

	void MoveFinished(bool bIsSuccessful);

	void LookAtPlayerCharacter() const;

	UFUNCTION()
	void ApplyDamageToPlayer(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
public:
	UFUNCTION(BlueprintCallable)
	void OnMoveRandomPointInRadius(FVector OriginLocation, float Radius, FVector& DestLocation);

	UFUNCTION(BlueprintCallable)
	void OnMoveToLocation(FVector Destination);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnMoveFinished(bool bIsSuccess);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnApplyDamageToPlayer(FName NotifyName);
	
	virtual void Update(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlledObject")
	class AMonsterCharacterBase* MyMonsterCharacter = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlledObject")
	class AAIControllerBase* MyAIController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	class APlayerCharacterBase* MyPlayerCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float DefaultWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool bIsLookAtPlayer = true;
public:
	[[nodiscard]] float GetDefaultWalkSpeed() const { return DefaultWalkSpeed; }

	UFUNCTION(BlueprintCallable, Category = "Default")
	[[nodiscard]] FVector GetPlayerLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Default")
	[[nodiscard]] float GetDistanceToPlayer() const;
	
};
