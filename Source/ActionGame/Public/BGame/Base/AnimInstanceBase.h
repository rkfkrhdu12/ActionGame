// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstanceBase();

	UFUNCTION()
	void EnterState(const FName& StateName);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnEnterStateEvent(const FName& StateName);
	
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	TObjectPtr<class ACharacterBase> MyCharacter = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	TObjectPtr<USkeletalMeshComponent> MyMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int CurrentStateIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	TArray<FName> States;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MoveSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	FVector MoveVelocity = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	FVector MoveDirection = FVector::ZeroVector;

public:
	UFUNCTION(BlueprintCallable, meta=(DataTablePin="DataTable", RowNamePin="RowData"), Category="State")
	bool IsEqualCurState(UDataTable* DataTable, FName RowData);
	
	UFUNCTION(BlueprintCallable)
	FName GetCurrentState();
	virtual void PostInitProperties() override;
};

