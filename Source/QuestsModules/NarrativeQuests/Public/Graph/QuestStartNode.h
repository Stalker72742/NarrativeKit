// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "Graph/QuestNodeBase.h"
#include "QuestStartNode.generated.h"

/**
 * @brief Entry point of the quest. Always exists in the graph and cannot be deleted or duplicated.
 */
UCLASS()
class NARRATIVEQUESTS_API UQuestStartNode : public UQuestNodeBase
{
    GENERATED_BODY()

public:
    /** @brief Constructor. */
    UQuestStartNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    // --- Parent class overrides ---

    virtual void AllocateDefaultPins() override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetTooltipText() const override;

#if WITH_EDITOR
    virtual bool CanUserDeleteNode() const override { return false; }
    virtual bool CanDuplicateNode() const override { return false; }
#endif
};
