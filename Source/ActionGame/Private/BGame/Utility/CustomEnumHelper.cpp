// Fill out your copyright notice in the Description page of Project Settings.

#include "BGame/Utility/CustomEnumHelper.h"

#include "BGame/Utility/CustomEnumTable.h"

auto UCustomEnumHelper::Register(const class UCustomEnumTable* EnumTable) -> bool
{
	if (EnumTable)
	{
		FString ListName = EnumTable->GetListName();
		if (!ListName.IsEmpty() && EnumTable->GetEnumNames().Num() > 0)
		{
			if (EnumMap.Contains(ListName))
			{
				if (EnumMap.Find(ListName)->Num() != EnumTable->GetEnumNames().Num())
					EnumMap.Remove(ListName);
				else
					return false;
			}
			
			if (!EnumMap.Contains(ListName))
			{
				EnumMap.Add(ListName, EnumTable->GetEnumNames());
			}
		}
	}

	return true;
}

int32 UCustomEnumHelper::GetEnumIndex(const FString& ListName, const FString& EnumValue)
{
	if (!EnumMap.Contains(ListName)) return -1;

	return EnumMap[ListName].IndexOfByKey(EnumValue);
}

FString UCustomEnumHelper::GetEnum(const FString& ListName, int32 Index)
{
	if (EnumMap.Contains(ListName))
	{
		auto it = EnumMap.Find(ListName);
		if (it->Num() > Index)
		{
			return (*it)[Index];
		}
	}

	return FString();
}

TArray<FString> UCustomEnumHelper::GetEnumNames(const FString& ListName)
{
	if (EnumMap.Contains(ListName))
		return *EnumMap.Find(ListName);

	return TArray<FString>();
}
