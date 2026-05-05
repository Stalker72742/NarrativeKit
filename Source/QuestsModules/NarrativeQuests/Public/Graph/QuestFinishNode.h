// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "Graph/QuestNodeBase.h"
#include "QuestFinishNode.generated.h"

/**
 * @brief Terminal node of a quest branch. Multiple instances are allowed.
 *        Marks the quest as success or failure depending on bIsSuccess.
 */
UCLASS()
class NARRATIVEQUESTS_API UQuestFinishNode : public UQuestNodeBase
{
    GENERATED_BODY()

public:
    /** @brief Constructor. */
    UQuestFinishNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    // --- EditDefaultsOnly (config) fields ---

    /** @brief If true the quest finishes successfully, otherwise it ends in failure. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest")
    bool bIsSuccess = true;

public:
    // --- Parent class overrides ---

    virtual void AllocateDefaultPins() override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetTooltipText() const override;

public:
    // --- Const getters ---

    /** @brief Returns whether this finish node represents a success outcome. */
    FORCEINLINE bool IsSuccess() const { return bIsSuccess; }
};
