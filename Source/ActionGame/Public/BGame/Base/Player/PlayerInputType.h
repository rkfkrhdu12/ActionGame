// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputType.generated.h"

UENUM(BlueprintType)
enum class EPlayerInputType : uint8
{
	Move UMETA(DisplayName = "Move"),
	Look UMETA(DisplayName = "Look"),
	Attack UMETA(DisplayName = "Attack"),
	Parry  UMETA(DisplayName = "Parry"),
	Dash  UMETA(DisplayName = "Dash"),
	LookAtTarget UMETA(DisplayName = "LookAtTarget"),
	NUM UMETA(Hidden)
};
