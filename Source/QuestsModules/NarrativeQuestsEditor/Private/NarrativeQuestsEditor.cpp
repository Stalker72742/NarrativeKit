#include "NarrativeQuestsEditor.h"

#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"
#include "KismetCompiler.h"
#include "KismetCompilerModule.h"
#include "Asset/FQuestsGraphAssetActions.h"
#include "Compiler/QuestBlueprintCompiler.h"
#include "Graph/QuestNodeBase.h"
#include "Graph/QuestStartNode.h"
#include "Graph/QuestFinishNode.h"
#include "Graph/SBaseQuestGraphNode.h"
#include "Graph/SQuestStartNode.h"
#include "Graph/SQuestFinishNode.h"
#include "Quest.h"
#include "QuestBlueprintGeneratedClass.h"
#include "Graph/QuestAsset.h"

#define LOCTEXT_NAMESPACE "FNarrativeQuestsEditorModule"

struct FQuestsNodeFactory : FGraphPanelNodeFactory
{
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UQuestStartNode* startNode = Cast<UQuestStartNode>(Node))
		{
			return SNew(SQuestStartNode, startNode);
		}
		if (UQuestFinishNode* finishNode = Cast<UQuestFinishNode>(Node))
		{
			return SNew(SQuestFinishNode, finishNode);
		}
		if (UQuestNodeBase* baseNode = Cast<UQuestNodeBase>(Node))
		{
			return SNew(SBaseQuestGraphNode, baseNode);
		}
		return nullptr;
	}
};

void FNarrativeQuestsEditorModule::StartupModule()
{
	NodeFactory = MakeShareable(new FQuestsNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(NodeFactory);

	IKismetCompilerInterface& kismetCompilerModule = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler");
	QuestCompiler = MakeShared<FQuestBlueprintCompiler>();
	kismetCompilerModule.GetCompilers().Add(QuestCompiler.Get());
	kismetCompilerModule.OverrideBPTypeForClass(UQuest::StaticClass(), UQuestAsset::StaticClass());

	FKismetCompilerContext::RegisterCompilerForBP(UQuestAsset::StaticClass(),
		[](UBlueprint* InBlueprint, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions)
		{
			return MakeShared<FQuestBlueprintCompilerContext>(
				CastChecked<UQuestAsset>(InBlueprint), InMessageLog, InCompileOptions);
		});

	UE_LOG(LogTemp, Warning, TEXT("[NarrativeQuestsEditor] Registered FQuestBlueprintCompiler + RegisterCompilerForBP. Total compilers: %d"),
		kismetCompilerModule.GetCompilers().Num());

	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	NarrativeAssetCategory = assetTools.RegisterAdvancedAssetCategory(
		FName("NarrativeKit"),
		FText::FromString("Narrative Kit")
	);

	assetTools.RegisterAssetTypeActions(MakeShareable(new FQuestsGraphAssetActions(NarrativeAssetCategory)));
}

void FNarrativeQuestsEditorModule::ShutdownModule()
{
	FEdGraphUtilities::UnregisterVisualNodeFactory(NodeFactory);

	if (QuestCompiler.IsValid() && FModuleManager::Get().IsModuleLoaded("KismetCompiler"))
	{
		IKismetCompilerInterface& kismetCompilerModule = FModuleManager::GetModuleChecked<IKismetCompilerInterface>("KismetCompiler");
		kismetCompilerModule.GetCompilers().Remove(QuestCompiler.Get());
		QuestCompiler.Reset();
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNarrativeQuestsEditorModule, NarrativeQuestsEditor)
