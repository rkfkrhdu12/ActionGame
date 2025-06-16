// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomInputKeyRow.generated.h"

/**
 * 
 */
USTRUCT()
struct ACTIONGAME_API FCustomInputKeyRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Row")
	FString Info;
};
