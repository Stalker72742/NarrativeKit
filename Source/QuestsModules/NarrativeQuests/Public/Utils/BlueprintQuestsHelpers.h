// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FQuestStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintQuestsHelpers.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FQuestDynamicDelegate, const FGameplayTag&, InQuest);

/**
 * 
 */
UCLASS()
class NARRATIVEQUESTS_API UBlueprintQuestsHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	/**
	 * @brief Broadcasts OnQuestChanged delegate on the given quest struct.
	 * @param InQuestStruct Target quest struct.
	 * @param InQuest Quest tag to broadcast.
	 */
	UFUNCTION(BlueprintCallable, Category="Quest")
	static void BroadcastQuestChanged(UPARAM(ref) FQuestStruct& InQuestStruct, const FGameplayTag& InQuest);

	/**
	 * @brief Binds a dynamic delegate to OnQuestChanged of the given quest struct.
	 * @param InQuestStruct Target quest struct.
	 * @param InDelegate Delegate to bind.
	 */
	UFUNCTION(BlueprintCallable, Category="Quest")
	static void BindQuestChanged(UPARAM(ref) FQuestStruct& InQuestStruct, UPARAM(DisplayName="Event") FQuestDynamicDelegate InDelegate);
};
