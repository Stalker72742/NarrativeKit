//Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FQuestStruct.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestChanged, const FGameplayTag&, InQuest);

USTRUCT(Blueprintable, BlueprintType)
struct FQuestStruct
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag QuestTag;
	
	FQuestChanged OnQuestChanged;
	
	FQuestStruct()
	{
		OnQuestChanged = FQuestChanged();
	}
};