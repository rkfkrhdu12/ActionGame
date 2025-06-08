// Fill out your copyright notice in the Description page of Project Settings.

#include "BGame/Utility/CustomEnumTable.h"

#include "BGame/Utility/CustomEnumHelper.h"

void UCustomEnumTable::Register() const
{
	UCustomEnumHelper::Register(this);
}

int32 UCustomEnumTable::GetEnumIndex(FString EnumName) const
{
	return EnumNames.IndexOfByKey(EnumName);
}

void UCustomEnumTable::PostInitProperties()
{
	UObject::PostInitProperties();
	
	Register();
}
