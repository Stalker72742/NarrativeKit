// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "KismetCompilerModule.h"
#include "KismetCompiler.h"

class UBlueprint;
class UQuestAsset;
struct FKismetCompilerOptions;
class FCompilerResultsLog;

/**
 * @brief Blueprint compiler handler for UQuestAsset.
 *        Spawns FQuestBlueprintCompilerContext which knows how to skip the custom QuestGraph
 *        during ubergraph merge (since it does not use K2 schema).
 */
class NARRATIVEQUESTSEDITOR_API FQuestBlueprintCompiler : public IBlueprintCompiler
{
public:
    virtual bool CanCompile(const UBlueprint* Blueprint) override;
    virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) override;
    virtual bool GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const override;
};

/**
 * @brief Compiler context for UQuestAsset.
 * @note Hides non-K2 graphs (our QuestGraph) from MergeUbergraphPagesIn so the K2 compiler
 *       doesn't try to merge them into the standard ubergraph.
 */
class NARRATIVEQUESTSEDITOR_API FQuestBlueprintCompilerContext : public FKismetCompilerContext
{
protected:
    typedef FKismetCompilerContext Super;

public:
    FQuestBlueprintCompilerContext(UQuestAsset* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);

protected:
    virtual void MergeUbergraphPagesIn(UEdGraph* Ubergraph) override;
    virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject) override;
};
