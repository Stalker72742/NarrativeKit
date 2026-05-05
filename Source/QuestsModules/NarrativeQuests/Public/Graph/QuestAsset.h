// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "QuestAsset.generated.h"

class UEdGraph;

/**
 * @brief Blueprint asset that authors a quest. Provides standard Blueprint UX
 * (Class Settings, Class Defaults, Variables, Event Graph) plus a custom narrative QuestGraph.
 */
UCLASS(BlueprintType)
class NARRATIVEQUESTS_API UQuestAsset : public UBlueprint
{
    GENERATED_BODY()

public:
    /** @brief Constructor. */
    UQuestAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    // --- Runtime fields ---

    /** @brief Custom narrative graph (separate from UbergraphPages / FunctionGraphs). */
    UPROPERTY()
    TObjectPtr<UEdGraph> QuestGraph;

public:
    // --- Parent class overrides ---

#if WITH_EDITOR
    virtual UClass* GetBlueprintClass() const override;
    virtual bool SupportedByDefaultBlueprintFactory() const override { return false; }
    virtual bool AlwaysCompileOnLoad() const override { return false; }
#endif

    virtual void PostLoad() override;

public:
    // --- Public functions ---

    /** @brief Sets the narrative quest graph instance. */
    void SetQuestGraph(UEdGraph* InGraph);

public:
    // --- Const getters ---

    /** @brief Returns the narrative quest graph. */
    FORCEINLINE UEdGraph* GetQuestGraph() const { return QuestGraph; }
};
