// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyValidTaskOutput.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutputSignature);

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UMyValidTaskOutput : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnOutputSignature OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FOnOutputSignature OnFailed;
};
