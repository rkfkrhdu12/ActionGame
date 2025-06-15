// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserdefinedState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Meta = (BlueprintSpawnableComponent), EditInlineNew, DefaultToInstanced)
class ACTIONGAME_API UUserdefinedState : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize(class ACharacterBase* Character);

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
	bool CanChanged(const FName& NextState);
	bool CanChanged_Implementation(const FName& NextState);

protected:
	UPROPERTY()
	bool bIsInitialized = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsEnabled = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Notify)
	TArray<FString> NotifyNameList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class ACharacterBase> MyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class AController> MyController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class USkeletalMeshComponent> MyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class UAnimInstanceBase> MyAnimInstance;

public:
	bool IsInitialized() const { return bIsInitialized; }

	UFUNCTION(BlueprintCallable)
	virtual bool IsValidValues() const;
};
