// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BGame/Utility/CustomDelegates.h"
#include "AIControllerBase.generated.h"

class APlayerCharacterBase;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
	AAIControllerBase();

	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnSearchPlayer;
	UPROPERTY(BlueprintAssignable, EditAnywhere, BlueprintCallable, Category = Input)
	FOnCharacterInput OnFindPlayer;
public:
	UFUNCTION(BlueprintCallable)
	void SearchPlayer(AActor* FindActor);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FindPlayer(APlayerCharacterBase* Player);

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bIsFindPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APlayerCharacterBase* PlayerCharacter = nullptr;
};
