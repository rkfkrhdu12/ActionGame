// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BGame/Utility/CustomDelegates.h"
#include "StateEventHandle.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UStateEventHandle : public UObject
{
	GENERATED_BODY()
public:
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

	///////////////////////// Notify
	FOnAnimNotify OnAnimNotify;
public:

	// 상태 이벤트 호출용 함수
	void BroadcastPreStateChanged(const FName& OldState, const FName& NewState) const;
	void BroadcastEnterState(const FName& StateName) const;
	void BroadcastStateChanged(const FName& StateName) const;
	void BroadcastExitState(const FName& StateName) const;
	void BroadcastPostStateChanged(const FName& OldState, const FName& NewState) const;
	
	void BroadcastAnimNotify(const UDataTable* DataTableRef,
											   FName SelectedRowName,
											   const FAnimNotifyEventReference& EventReference) const;
};
