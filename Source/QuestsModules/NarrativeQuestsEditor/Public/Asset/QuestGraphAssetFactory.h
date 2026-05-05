// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "QuestGraphAssetFactory.generated.h"

/**
 * @brief Factory that creates a UQuestAsset (Blueprint subclass) via FKismetEditorUtilities::CreateBlueprint.
 */
UCLASS()
class NARRATIVEQUESTSEDITOR_API UQuestGraphAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UQuestGraphAssetFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent,
		FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
