// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "GraphBase/BaseGraphNode.h"
#include "QuestNodeBase.generated.h"

class UQuestTaskBase;
/**
 * @brief Base node for the quest graph. Subclass to add quest-specific data and behavior.
 */
UCLASS(Blueprintable, BlueprintType)
class NARRATIVEQUESTS_API UQuestNodeBase : public UBaseGraphNode
{
    GENERATED_BODY()
public:
    
    UPROPERTY(EditAnywhere, Instanced, Category="Tasks")
    UQuestTaskBase* QuestTask;
};
