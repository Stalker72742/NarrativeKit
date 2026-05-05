// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestTaskBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class NARRATIVEQUESTS_API UQuestTaskBase : public UObject
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category="Display")
	FText TaskDisplayName;
	
	UPROPERTY(EditAnywhere, Category="Display")
	FText TaskDisplayDescription;
};
