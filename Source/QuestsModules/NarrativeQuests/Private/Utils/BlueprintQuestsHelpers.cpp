// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/BlueprintQuestsHelpers.h"

void UBlueprintQuestsHelpers::BroadcastQuestChanged(FQuestStruct& InQuestStruct, const FGameplayTag& InQuest)
{
	InQuestStruct.OnQuestChanged.Broadcast(InQuest);
}

void UBlueprintQuestsHelpers::BindQuestChanged(FQuestStruct& InQuestStruct, FQuestDynamicDelegate InDelegate)
{
	InQuestStruct.OnQuestChanged.Add(InDelegate);
}
