// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"

class UQuestAsset;
class SDockTab;

/**
 * @brief Quest editor toolkit. Extends FBlueprintEditor so we get standard Blueprint UX
 * (Class Settings, Class Defaults, Variables, Event Graph, Compile) and adds a custom QuestGraph tab.
 */
class NARRATIVEQUESTSEDITOR_API FQuestGraphEditorToolkit : public FBlueprintEditor
{
public:
	/** @brief Initializes the editor for the given quest asset. */
	void InitQuestEditor(const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost,
		UQuestAsset* InQuestAsset);

public:
	// --- Parent class overrides ---

	virtual FName GetToolkitFName() const override { return FName("QuestGraphEditor"); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("Quest Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("Quest "); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.4f, 0.6f, 1.0f); }

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	virtual void JumpToHyperlink(const UObject* ObjectReference, bool bRequestRename = false) override;

protected:
	// --- Service / helper functions ---

	TSharedRef<SDockTab> SpawnQuestGraphTab(const FSpawnTabArgs& Args);

protected:
	// --- Runtime fields ---

	UQuestAsset* QuestAsset { nullptr };

	static const FName QuestGraphTabId;
};
