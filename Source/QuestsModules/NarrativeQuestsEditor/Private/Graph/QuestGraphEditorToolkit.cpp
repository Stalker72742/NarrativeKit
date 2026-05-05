// Created by Stalker7274

#include "Graph/QuestGraphEditorToolkit.h"

#include "Graph/QuestAsset.h"
#include "Graph/QuestGraphSchema.h"
#include "EdGraph/EdGraph.h"
#include "Editor.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Commands/GenericCommands.h"
#include "Framework/Commands/UICommandList.h"
#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"

const FName FQuestGraphEditorToolkit::QuestGraphTabId = FName("QuestGraphTab");

void FQuestGraphEditorToolkit::InitQuestEditor(const EToolkitMode::Type InMode,
	const TSharedPtr<IToolkitHost>& InToolkitHost,
	UQuestAsset* InQuestAsset)
{
	QuestAsset = InQuestAsset;

	TArray<UBlueprint*> blueprints;
	blueprints.Add(InQuestAsset);

	InitBlueprintEditor(InMode, InToolkitHost, blueprints, /*bShouldOpenInDefaultsMode=*/ false);

	if (UEdGraph* questGraph = InQuestAsset->GetQuestGraph())
	{
		OpenDocument(questGraph, FDocumentTracker::OpenNewDocument);
	}
}

void FQuestGraphEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FBlueprintEditor::RegisterTabSpawners(InTabManager);
	
	InTabManager->RegisterTabSpawner(QuestGraphTabId,
		FOnSpawnTab::CreateSP(this, &FQuestGraphEditorToolkit::SpawnQuestGraphTab))
		.SetDisplayName(FText::FromString("Quest Graph"));
}

void FQuestGraphEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FBlueprintEditor::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(QuestGraphTabId);
}

void FQuestGraphEditorToolkit::JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename)
{
	if (const UEdGraph* graph = Cast<const UEdGraph>(ObjectReference))
	{
		if (graph->Schema && graph->Schema->IsChildOf(UQuestGraphSchema::StaticClass()) || 
			graph->Schema->IsChildOf(UEdGraphSchema_K2::StaticClass()))
		{
			const FDocumentTracker::EOpenDocumentCause openMode =
				FSlateApplication::Get().GetModifierKeys().IsShiftDown()
					? FDocumentTracker::ForceOpenNewDocument
					: FDocumentTracker::OpenNewDocument;

			OpenDocument(const_cast<UEdGraph*>(graph), openMode);
			return;
		}
	}

	FBlueprintEditor::JumpToHyperlink(ObjectReference, bRequestRename);
}

TSharedRef<SDockTab> FQuestGraphEditorToolkit::SpawnQuestGraphTab(const FSpawnTabArgs& Args)
{
	UEdGraph* graph = QuestAsset ? QuestAsset->GetQuestGraph() : nullptr;

	FGraphAppearanceInfo appearance;
	appearance.CornerText = FText::FromString("QUEST");

	TSharedRef<FUICommandList> graphCommands = MakeShared<FUICommandList>();
	graphCommands->MapAction(
		FGenericCommands::Get().Undo,
		FExecuteAction::CreateLambda([]()
		{
			if (GEditor) { GEditor->UndoTransaction(); }
		})
	);
	graphCommands->MapAction(
		FGenericCommands::Get().Redo,
		FExecuteAction::CreateLambda([]()
		{
			if (GEditor) { GEditor->RedoTransaction(); }
		})
	);

	TSharedRef<SGraphEditor> graphEditor = SNew(SGraphEditor)
		.GraphToEdit(graph)
		.Appearance(appearance)
		.AdditionalCommands(graphCommands);

	return SNew(SDockTab)
		.AccessibleText(FText::FromString("Quest Graph"))
		.Label(FText::FromString("Quest Graph"))
		[
			graphEditor
		];
}
