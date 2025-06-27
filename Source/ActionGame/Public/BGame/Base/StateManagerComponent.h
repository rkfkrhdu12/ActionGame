// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateManagerComponent.generated.h"


class UUserdefinedState;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UStateManagerComponent();

	UFUNCTION(BlueprintCallable)
	virtual void ChangeState(const FName& NextState);

	void AnimNotify(const UDataTable* DataTablePtr,
					FName SelectedRowName,
					const FAnimNotifyEventReference& EventReference) const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void PostInitProperties() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY(EditAnywhere)
	class ACharacterBase* MyCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	FName CurrentEnableStateName;

	UPROPERTY()
	UUserdefinedState* CurrentState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FName DefaultResetStateName = "Idle";
public:
	FName GetCurrentStateName() const { return CurrentEnableStateName; }

	UFUNCTION(BlueprintCallable)
	void SetTickInterval(float Interval);
};
