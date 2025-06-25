// Fill out your copyright notice in the Description page of Project Settings.


#include "BGame/Base/StateEventHandle.h"

void UStateEventHandle::BroadcastPreStateChanged(const FName& OldState, const FName& NewState) const
{
	if (OnPreStateChanged.IsBound())
		OnPreStateChanged.Broadcast(OldState, NewState);
}

void UStateEventHandle::BroadcastEnterState(const FName& StateName) const
{
	if (OnEnterState.IsBound())
		OnEnterState.Broadcast(StateName);
}

void UStateEventHandle::BroadcastStateChanged(const FName& StateName) const
{
	if (OnStateChanged.IsBound())
		OnStateChanged.Broadcast(StateName);
}

void UStateEventHandle::BroadcastExitState(const FName& StateName) const
{
	if (OnExitState.IsBound())
		OnExitState.Broadcast(StateName);
}

void UStateEventHandle::BroadcastPostStateChanged(const FName& OldState, const FName& NewState) const
{
	if (OnPostStateChanged.IsBound())
		OnPostStateChanged.Broadcast(OldState, NewState);
}

void UStateEventHandle::BroadcastAnimNotify(const UDataTable* DataTableRef, FName SelectedRowName,
                                            const FAnimNotifyEventReference& EventReference) const
{
	if (OnAnimNotify.IsBound())
		OnAnimNotify.Broadcast(DataTableRef, SelectedRowName, EventReference);
}
