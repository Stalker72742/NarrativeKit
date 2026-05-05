// Created by Stalker7274

#include "Compiler/QuestBlueprintCompiler.h"

#include "Graph/QuestAsset.h"
#include "Graph/QuestGraphSchema.h"
#include "Quest.h"
#include "QuestBlueprintGeneratedClass.h"
#include "EdGraphSchema_K2.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestCompiler, Log, All);

bool FQuestBlueprintCompiler::CanCompile(const UBlueprint* Blueprint)
{
    const bool bCanCompile = Cast<UQuestAsset>(Blueprint) != nullptr;
    UE_LOG(LogQuestCompiler, Log, TEXT("[QuestCompiler] CanCompile(%s) -> %s"),
        Blueprint ? *Blueprint->GetName() : TEXT("null"),
        bCanCompile ? TEXT("true") : TEXT("false"));
    return bCanCompile;
}

void FQuestBlueprintCompiler::Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results)
{
    UE_LOG(LogQuestCompiler, Log, TEXT("[QuestCompiler] Compile(%s) called"),
        Blueprint ? *Blueprint->GetName() : TEXT("null"));

    if (UQuestAsset* questAsset = CastChecked<UQuestAsset>(Blueprint))
    {
        FQuestBlueprintCompilerContext compiler(questAsset, Results, CompileOptions);
        compiler.Compile();
        check(compiler.NewClass);
    }
}

bool FQuestBlueprintCompiler::GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const
{
    if (ParentClass && (ParentClass == UQuest::StaticClass() || ParentClass->IsChildOf(UQuest::StaticClass())))
    {
        OutBlueprintClass = UQuestAsset::StaticClass();
        OutBlueprintGeneratedClass = UQuestBlueprintGeneratedClass::StaticClass();
        return true;
    }

    return false;
}

FQuestBlueprintCompilerContext::FQuestBlueprintCompilerContext(UQuestAsset* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions)
    : Super(SourceSketch, InMessageLog, InCompilerOptions)
{
}

void FQuestBlueprintCompilerContext::MergeUbergraphPagesIn(UEdGraph* Ubergraph)
{
    TArray<TObjectPtr<UEdGraph>> backupPages = Blueprint->UbergraphPages;

    Blueprint->UbergraphPages.RemoveAll([](const TObjectPtr<UEdGraph>& Graph)
    {
        return Graph != nullptr
            && Graph->Schema != nullptr
            && !Graph->Schema->IsChildOf(UEdGraphSchema_K2::StaticClass());
    });

    Super::MergeUbergraphPagesIn(Ubergraph);

    Blueprint->UbergraphPages = backupPages;
}

void FQuestBlueprintCompilerContext::CopyTermDefaultsToDefaultObject(UObject* DefaultObject)
{
    Super::CopyTermDefaultsToDefaultObject(DefaultObject);

    UQuest* questCDO = Cast<UQuest>(DefaultObject);
    if (!questCDO)
    {
        UE_LOG(LogQuestCompiler, Warning, TEXT("[QuestCompiler] CopyTermDefaultsToDefaultObject: DefaultObject is not UQuest (got %s)"),
            DefaultObject ? *DefaultObject->GetClass()->GetName() : TEXT("null"));
        return;
    }

    UEdGraph* questGraph = nullptr;
    for (UEdGraph* page : Blueprint->UbergraphPages)
    {
        if (page && page->Schema && page->Schema->IsChildOf(UQuestGraphSchema::StaticClass()))
        {
            questGraph = page;
            break;
        }
    }

    if (UQuestAsset* questAsset = Cast<UQuestAsset>(Blueprint); questGraph == nullptr && questAsset)
    {
        questGraph = questAsset->GetQuestGraph();
    }

    int32 nodeCount = 0;
    if (questGraph)
    {
        for (const TObjectPtr<UEdGraphNode>& node : questGraph->Nodes)
        {
            if (node)
            {
                ++nodeCount;
            }
        }
    }

    questCDO->SetNodeCount(nodeCount);

    UE_LOG(LogQuestCompiler, Log, TEXT("[QuestCompiler] Stamped CDO %s: NodeCount = %d (graph: %s)"),
        *questCDO->GetName(),
        nodeCount,
        questGraph ? *questGraph->GetName() : TEXT("none"));
}
