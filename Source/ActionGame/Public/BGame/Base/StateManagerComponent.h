// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateManagerComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStateChanged, const FString&, CurrentState, const FString&, OriginState, const FString&, ChangedState);

UCLASS(Blueprintable, EditInlineNew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONGAME_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UStateManagerComponent();

public:
	void ChangeState(const FString& NextState);
	FOnStateChanged OnStateChanged;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class APlayerCharacterBase> MyCharacter = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class APlayerControllerBase> MyController = nullptr;
	void InitializeComponents();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "State", meta = (AllowPrivateAccess = "true"))
	class UCustomEnumTable* UseStateEnum = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "State", meta = (AllowPrivateAccess = "true"))
	TMap<FString, class UUserdefinedState*> StateList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	class UUserdefinedState* CurrentState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	class UUserdefinedState* PrevState = nullptr;
	void InitializeStateList();
		
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UUserdefinedState* GetCurrentState() const { return CurrentState; }
	
	UFUNCTION()
	void InputAttack(bool InputValue);
};
