// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StateManagerComponent.h"
#include "GameFramework/Character.h"
#include "BGame/Utility/CustomDelegates.h"
#include "CharacterBase.generated.h"

UCLASS(BlueprintType)
class ACTIONGAME_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	ACharacterBase();
	
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	
public:
	void ChangeState(const FName& NextState) const;
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf = "Target", DataTablePin="EnumTable", RowNamePin="State"), Category="State")
	static void ChangeState(ACharacterBase* Target, UDataTable* EnumTable, FName State);

	/////////////////////////////// Delegate / Event
public:
	////////////////////////// State
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = State, meta = (AllowPrivateAccess = "true"), AdvancedDisplay)
	FOnStateChanged OnPreStateChanged;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = State, meta = (AllowPrivateAccess = "true"), AdvancedDisplay)
	FOnStateChange OnEnterState;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = State, meta = (AllowPrivateAccess = "true"), AdvancedDisplay)
	FOnStateChange OnStateChanged;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = State, meta = (AllowPrivateAccess = "true"), AdvancedDisplay)
	FOnStateChange OnExitState;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = State, meta = (AllowPrivateAccess = "true"), AdvancedDisplay)
	FOnStateChanged OnPostStateChanged;

	///////////////////////// Input
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInputVector2D OnInputMoveDirection;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnInputAttack;

	//////////////////////////////// Components
protected:	
	//					   State Manager	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	class UStateManagerComponent* StateManager = nullptr;
	
	//					   Action Manager	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action, meta = (AllowPrivateAccess = "true"))
	class UActionManagerComponent* ActionManager = nullptr;

	//////////////////////////////// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	UDataTable* StateList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	TArray<class UUserdefinedState*> StateClassList;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true", EditCondition = false, EditConditionHides))
	TArray<FName> StateNames;
public: //		Get Function
	class UActionManagerComponent* GetActionManager() const { return ActionManager; }
	class UStateManagerComponent* GetStateManager() const { return StateManager; }

	auto GetStateIndex(const FName& StateName) const -> int32;

	TArray<class UUserdefinedState*> GetStateClassList() const { return StateClassList; }
	TArray<FName> GetStateNames() const { return StateNames; }
	//////////////////////////////// Debug
public:
	// virtual void Tick(float DeltaSeconds) override;
	// virtual void PostInitProperties() override;
	// virtual void PostLoad() override;
	// virtual void PostActorCreated() override;
	// virtual void OnConstruction(const FTransform& Transform) override;

	void TestFunc(const FString fName) const
	{
		if (StateManager)
		{
			UE_LOG(LogTemp, Display, TEXT("%s %s %s"), *GetName(), *fName, *StateManager->GetFullName());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s %s %d"), *GetName(), *fName, StateManager != nullptr);
		}
	}

};
