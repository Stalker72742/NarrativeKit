#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"

struct FQuestsNodeFactory;
class FQuestBlueprintCompiler;

class FNarrativeQuestsEditorModule : public IModuleInterface
{
protected:
    TSharedPtr<FQuestsNodeFactory> NodeFactory;
    TSharedPtr<FQuestBlueprintCompiler> QuestCompiler;

    EAssetTypeCategories::Type NarrativeAssetCategory {EAssetTypeCategories::Type::Misc};

public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
