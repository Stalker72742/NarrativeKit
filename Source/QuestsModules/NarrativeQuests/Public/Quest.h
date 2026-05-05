// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "Quest.generated.h"

class FQuestBlueprintCompilerContext;

/**
 * @brief Base runtime class for a quest. Subclass via QuestAsset (Blueprint) to author quest logic.
 */
UCLASS(Blueprintable, BlueprintType)
class NARRATIVEQUESTS_API UQuest : public UObject
{
    GENERATED_BODY()

    friend class FQuestBlueprintCompilerContext;

public:
    /** @brief Constructor. */
    UQuest(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    // --- EditDefaultsOnly (config) fields ---

    /** @brief Human-readable name of the quest. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
    FText DisplayName;

    /** @brief Quest description shown to the player. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(MultiLine=true), Category="Quest")
    FText Description;

    /** @brief Gameplay tag identifying this quest (e.g. Quest.Tutorial.Intro). */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
    FGameplayTag QuestTag;

protected:
    // --- Compiler-written fields (read-only at edit time) ---

    /** @brief Total node count in the quest graph. Written by the compiler. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|Compiled")
    int32 NodeCount = 0;

protected:
    // --- Service / helper functions (used by the compiler only) ---

    /** @brief Setter used by FQuestBlueprintCompilerContext when stamping data into the CDO. */
    void SetNodeCount(int32 InNodeCount) { NodeCount = InNodeCount; }

public:
    // --- Const getters ---

    /** @brief Returns the human-readable quest name. */
    FORCEINLINE FText GetDisplayName() const { return DisplayName; }

    /** @brief Returns the quest description. */
    FORCEINLINE FText GetDescription() const { return Description; }

    /** @brief Returns the gameplay tag identifying this quest. */
    FORCEINLINE FGameplayTag GetQuestTag() const { return QuestTag; }

    /** @brief Returns the number of nodes in the quest graph (filled by the compiler). */
    FORCEINLINE int32 GetNodeCount() const { return NodeCount; }
};
