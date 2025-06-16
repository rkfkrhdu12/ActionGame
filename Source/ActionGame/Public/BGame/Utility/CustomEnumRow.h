// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CustomEnumRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ACTIONGAME_API FCustomEnumRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Enum Row")
	int32 ID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Enum Row")
	FName Name = "";
};
