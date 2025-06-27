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
	void FindPlayer();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	bool bIsFindPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	class AMonsterCharacterBase* MyCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	APlayerCharacterBase* MyPlayerCharacter = nullptr;

public:
	APlayerCharacterBase* GetPlayerCharacter() const { return MyPlayerCharacter; }

	UFUNCTION(BlueprintCallable)
	EPathFollowingStatus::Type GetCharacterStatus() const;
};
