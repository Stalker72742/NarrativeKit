// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

class UFactory;

/**
 * @brief Asset type actions for UQuestAsset (Blueprint subclass).
 * @note Inherits from FAssetTypeActions_Blueprint to integrate with the Blueprint pipeline
 *       (Compile, Class Settings, Class Defaults, etc.). Opens our custom FQuestGraphEditorToolkit.
 */
class NARRATIVEQUESTSEDITOR_API FQuestsGraphAssetActions : public FAssetTypeActions_Blueprint
{
public:

    FQuestsGraphAssetActions(EAssetTypeCategories::Type InCategory);

protected:
    EAssetTypeCategories::Type Category;

public:
    virtual FText GetName() const override { return FText::FromString("Quest"); }
    virtual FColor GetTypeColor() const override { return FColor(100, 150, 255); }
    virtual UClass* GetSupportedClass() const override;
    virtual uint32 GetCategories() override { return Category; }

    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
        TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

    virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;
};
