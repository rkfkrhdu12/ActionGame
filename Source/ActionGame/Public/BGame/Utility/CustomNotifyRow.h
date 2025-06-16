// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomNotifyRow.generated.h"

/**
 * 
 */
USTRUCT()
struct ACTIONGAME_API FCustomNotifyRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Row")
	FName Tag = "";
};
