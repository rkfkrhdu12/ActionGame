// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Utility/UserdefinedMontageNotify.h"
#include "UNotify_DataTableEvent.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUNotify_DataTableEvent : public UUserdefinedMontageNotify
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FDataTableRowHandle NotifyTableHandle;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
