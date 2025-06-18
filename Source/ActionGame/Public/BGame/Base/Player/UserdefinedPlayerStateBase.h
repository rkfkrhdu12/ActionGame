// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Base/UserdefinedState.h"
#include "UserdefinedPlayerStateBase.generated.h"

class APlayerCharacterBase;
enum class EPlayerInputType : uint8;
class APlayerControllerBase;
class UInputManagerComponent;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUserdefinedPlayerStateBase : public UUserdefinedState
{
	GENERATED_BODY()
public:
	virtual void Initialize(ACharacterBase* Character) override;
	virtual bool IsValidValues() const override;

	void InputKey(EPlayerInputType Type, bool bValue);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputKey(EPlayerInputType Type, bool bValue);

	UFUNCTION(BlueprintCallable, meta=(DataTablePin="EnumTable", RowNamePin="State"), Category="State")
	void ChangeCharacterState(UDataTable* EnumTable, FName State);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controller, meta = (AllowPrivateAccess = "true"))
	APlayerCharacterBase* MyPlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controller, meta = (AllowPrivateAccess = "true"))
	APlayerControllerBase* MyPlayerController;
};

