// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerBase();

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

protected:
	//											 
	//				Other Object ptr Variable			
	//											 
	UPROPERTY(EditAnywhere)
	TObjectPtr<class APlayerCharacterBase> MyCharacter;

	//					   Input Manager					  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputManagerComponent> InputManager;

private:
	void InitializeInputSystem() const;
	void BindInputActions() const;

public:
	UInputManagerComponent* GetInputManagerComponent() const { return InputManager; }
};
