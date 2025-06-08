// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class ACTIONGAME_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	ACharacterBase();
public:
	virtual void BeginPlay() override;

	
	UFUNCTION(BlueprintCallable)
	void ChangeState(const FString& NextState) const;

protected:
	//					   State Manager	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	class UStateManagerComponent* StateManager;
	
	//					   Action Manager	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Action, meta = (AllowPrivateAccess = "true"))
	class UActionManagerComponent* ActionManager;
public:
	class UActionManagerComponent* GetActionManager() const { return ActionManager; }
};
