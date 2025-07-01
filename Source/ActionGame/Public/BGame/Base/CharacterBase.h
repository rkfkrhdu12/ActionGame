// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "StateEventHandle.h"
#include "GameFramework/Character.h"
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
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& MoveDirection);
	
	void ChangeState(const FName& NextState) const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDrawDebugLine = true;
	UFUNCTION(BlueprintCallable)
	void LineTrace(FVector StartLocation, FVector EndLocation, FHitResult& OutHitResult);
	/////////////////////////////// Delegate / Event Handle
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition=false, HideEditCondition))
	class UStateEventHandle* StateEventHandler = nullptr;

	/////////////////////////////// Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	UDataTable* StateNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = State, meta = (AllowPrivateAccess = "true"))
	TArray<class UUserdefinedState*> StateList;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true", EditCondition = false, EditConditionHides))
	TArray<FName> StateNames;
	
	//////////////////////////////// Components
protected:	
	//					   State Manager	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	class UStateManagerComponent* StateManagerComp = nullptr;
	
	//////////////////////////////// Variables
public: //		Get Function
	class UStateManagerComponent* GetStateManager() const { return StateManagerComp; }
	class UStateEventHandle* GetStateEventHandle() const { return StateEventHandler; }
	
	UFUNCTION(BlueprintCallable)
	int32 GetStateIndex(const FName& StateName) const;

	TArray<class UUserdefinedState*> GetStateClassList() const;
	TArray<FName> GetStateNames() const ;

	UFUNCTION(BlueprintCallable)
	FName GetCurrentStateName() const;

	/////////////////////////////////// static Func
public:
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf = "Target", DataTablePin="EnumTable", RowNamePin="State"), Category="State")
	static void ChangeState(ACharacterBase* Target, UDataTable* EnumTable, FName State);

	UFUNCTION(BlueprintCallable, meta=(DataTablePin="DataTable", RowNamePin="RowData"), Category="State")
	static bool IsCompareTableData(UDataTable* DataTable, FName RowData, FName CompareName);
	
	//////////////////////////////// Debug
public:
	// virtual void Tick(float DeltaSeconds) override;
	// virtual void PostInitProperties() override;
	// virtual void PostLoad() override;
	// virtual void PostActorCreated() override;
	// virtual void OnConstruction(const FTransform& Transform) override;

	void TestFunc(const FString fName) const
	{
		if (false)
		if (auto CheckComp = StateEventHandler)
		{
			UE_LOG(LogTemp, Display, TEXT("%s %s %s"), *GetName(), *fName, *CheckComp->GetFullName());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s %s %d"), *GetName(), *fName, CheckComp != nullptr);
		}
	}

};
