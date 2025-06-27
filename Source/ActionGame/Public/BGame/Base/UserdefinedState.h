// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserdefinedState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Meta = (BlueprintSpawnableComponent), EditInlineNew, DefaultToInstanced)
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

	void AnimNotify(const UDataTable* DataTablePtr,
	                FName SelectedRowName,
	                const FAnimNotifyEventReference& EventReference);

	// BP
	
	/// My Variables Null Check Complete
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BeginPlay();

	/// My Variables Null Check Complete
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnEnable();
	/// My Variables Null Check Complete
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Tick(float DeltaTime);
	/// My Variables Null Check Complete
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnDisable();
	
	/// My Variables Null Check Complete
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnAnimNotify(const UDataTable* DataTableRef,
					FName SelectedRowName,
					const FAnimNotifyEventReference& EventReference);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanChanged(const FName& NextState);
	bool CanChanged_Implementation(const FName& NextState);

protected:
	UPROPERTY()
	bool bIsInitialized = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsEnabled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class ACharacterBase> MyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class AController> MyController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, AdvancedDisplay)
	TObjectPtr<class USkeletalMeshComponent> MyMesh;

public:
	bool IsInitialized() const { return bIsInitialized; }

	UFUNCTION(BlueprintCallable)
	virtual bool IsValidValues() const;
};
