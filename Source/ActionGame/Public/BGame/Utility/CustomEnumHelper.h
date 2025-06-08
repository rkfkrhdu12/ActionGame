// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomEnumHelper.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UCustomEnumHelper : public UObject
{
	GENERATED_BODY()
public:
	static bool Register(const class UCustomEnumTable* EnumTable);

	UFUNCTION(BlueprintCallable, Category = "Custom Enum Helper")
	static int32 GetEnumIndex(const FString& ListName, const FString& EnumValue);
	UFUNCTION(BlueprintCallable, Category = "Custom Enum Helper")
	static FString GetEnum(const FString& ListName, int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Custom Enum Helper")
	static TArray<FString> GetEnumNames(const FString& ListName);
private:
	inline static TMap<FString, TArray<FString>> EnumMap;
};
