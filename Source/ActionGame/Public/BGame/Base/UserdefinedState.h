// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserdefinedState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, Meta = (BlueprintSpawnableComponent), DefaultToInstanced)
class ACTIONGAME_API UUserdefinedState : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize(class ACharacterBase* Character, int32 ID);

	// BeginPlay
	virtual void Awake();
	
	virtual void Enable();
	virtual void Disable();
	virtual void Update(float DeltaTime);

	virtual void AnimStart(UAnimMontage* Montage);
	virtual void AnimComplete(UAnimMontage* Montage, bool bInterrupted);
	virtual void AnimBlendIn(UAnimMontage* Montage);
	virtual void AnimBlendOut(UAnimMontage* Montage, bool bInterrupted);
	virtual void AnimInterrupted();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BeginPlay();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnEnable();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Tick(float DeltaTime);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnDisable();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAnimStart(UAnimMontage* Montage);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAnimComplete(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAnimBlendIn(UAnimMontage* Montage);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAnimBlendOut(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAnimInterrupted();
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void OnAnimNotify(FString NotifyName);
	//void OnAnimNotify_Implementation(FString NotifyName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsChangeState(const FString& NextState);
	bool IsChangeState_Implementation(const FString& NextState);

protected:
	UPROPERTY()
	bool bIsInitialized = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsEnabled = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = false, EditConditionHides))
	FName CurrentStateName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = false, EditConditionHides))
	int32 Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
          meta=(RowType="/Script/ActionGame.CustomEnumRow"))
	FDataTableRowHandle CurrentState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Notify)
	TArray<FString> NotifyNameList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ACharacterBase> MyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AController> MyController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USkeletalMeshComponent> MyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimInstanceBase> MyAnimInstance;

public:
	bool IsInitialized() const { return bIsInitialized; }

	FString GetCurrentStateName() const { return CurrentStateName.ToString(); }
	int32 GetCurrentStateIndex() const { return Index; }

	UFUNCTION(BlueprintCallable)
	virtual bool IsValidValues() const;
};
