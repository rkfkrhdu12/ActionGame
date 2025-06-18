
#pragma once
#include "CoreMinimal.h"
#include "CustomDelegates.generated.h"

// Character Input Delegate
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterInputVector2D, FVector2D, Value);
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInput, bool, InputValue);

// Character State Delegate
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, const FName&, StateName);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChanged, const FName&, OldState,const FName&, NewState);



DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerInputVector2D, FVector2D Value);

// Character Notify Delegate
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAnimNotify, const UDataTable* DataTableRef,
                                               FName SelectedRowName,
                                               const FAnimNotifyEventReference& EventReference);
