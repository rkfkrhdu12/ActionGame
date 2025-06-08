// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomEnumTable.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, Meta = (BlueprintSpawnableComponent), DefaultToInstanced)
class ACTIONGAME_API UCustomEnumTable : public UObject
{
	GENERATED_BODY()
public:
	void Register() const;

	UFUNCTION(BlueprintCallable, Category = "Custom Enum")
	int32 GetEnumIndex(FString EnumName) const; 	
	UFUNCTION(BlueprintCallable, Category="Custom Enum")
	FString GetEnum(int32 Index) const { return EnumNames[Index]; }
	UFUNCTION(BlueprintCallable, Category="Custom Enum")
	FString GetListName() const { return ListName;}
	UFUNCTION(BlueprintCallable, Category="Custom Enum")
	TArray<FString> GetEnumNames() const { return EnumNames; }

	virtual void PostInitProperties() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum List")
	FString ListName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum List", meta = (AllowPrivateAccess = "true"))
	TArray<FString> EnumNames;
};
