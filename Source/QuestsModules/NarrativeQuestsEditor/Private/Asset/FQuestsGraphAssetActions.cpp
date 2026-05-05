// Created by Stalker7274

#include "Asset/FQuestsGraphAssetActions.h"

#include "Asset/QuestGraphAssetFactory.h"
#include "Graph/QuestAsset.h"
#include "Graph/QuestGraphEditorToolkit.h"

FQuestsGraphAssetActions::FQuestsGraphAssetActions(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

UClass* FQuestsGraphAssetActions::GetSupportedClass() const
{
	return UQuestAsset::StaticClass();
}

void FQuestsGraphAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (UObject* obj : InObjects)
	{
		if (UQuestAsset* asset = Cast<UQuestAsset>(obj))
		{
			TSharedRef<FQuestGraphEditorToolkit> toolkit = MakeShareable(new FQuestGraphEditorToolkit());
			toolkit->InitQuestEditor(mode, EditWithinLevelEditor, asset);
		}
	}
}

UFactory* FQuestsGraphAssetActions::GetFactoryForBlueprintType(UBlueprint* InBlueprint) const
{
	return NewObject<UQuestGraphAssetFactory>();
}
