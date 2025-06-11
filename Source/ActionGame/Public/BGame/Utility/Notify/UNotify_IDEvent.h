// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGame/Utility/UserdefinedMontageNotify.h"
#include "UNotify_IDEvent.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UUNotify_IDEvent : public UUserdefinedMontageNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notify, meta = (AllowPrivateAccess = "true"))
	int32 NotifyId;

	
};
