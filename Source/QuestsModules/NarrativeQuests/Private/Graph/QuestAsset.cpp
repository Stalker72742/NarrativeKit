// Created by Stalker7274

#include "Graph/QuestAsset.h"
#include "QuestBlueprintGeneratedClass.h"
#include "EdGraph/EdGraph.h"

UQuestAsset::UQuestAsset(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

#if WITH_EDITOR
UClass* UQuestAsset::GetBlueprintClass() const
{
    return UQuestBlueprintGeneratedClass::StaticClass();
}
#endif

void UQuestAsset::SetQuestGraph(UEdGraph* InGraph)
{
    QuestGraph = InGraph;
}

void UQuestAsset::PostLoad()
{
    Super::PostLoad();

    if (QuestGraph && !UbergraphPages.Contains(QuestGraph))
    {
        QuestGraph->bAllowDeletion = false;
        QuestGraph->bAllowRenaming = false;
        UbergraphPages.Add(QuestGraph);
    }
}
