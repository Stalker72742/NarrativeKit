// Created by Stalker7274

#include "Asset/QuestGraphAssetFactory.h"

#include "Graph/QuestAsset.h"
#include "Graph/QuestGraphSchema.h"
#include "Graph/QuestStartNode.h"
#include "Quest.h"
#include "QuestBlueprintGeneratedClass.h"
#include "EdGraph/EdGraph.h"
#include "Kismet2/KismetEditorUtilities.h"

UQuestGraphAssetFactory::UQuestGraphAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UQuestAsset::StaticClass();
}

UObject* UQuestGraphAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UQuestAsset* questAsset = CastChecked<UQuestAsset>(
		FKismetEditorUtilities::CreateBlueprint(
			UQuest::StaticClass(),
			InParent,
			Name,
			BPTYPE_Normal,
			UQuestAsset::StaticClass(),
			UQuestBlueprintGeneratedClass::StaticClass(),
			FName("QuestGraphAssetFactory")
		)
	);

	UEdGraph* questGraph = NewObject<UEdGraph>(questAsset, FName(TEXT("QuestGraph")), RF_Transactional);
	questGraph->Schema = UQuestGraphSchema::StaticClass();
	questGraph->bAllowDeletion = false;
	questGraph->bAllowRenaming = false;

	questAsset->UbergraphPages.Add(questGraph);
	questAsset->SetQuestGraph(questGraph);

	UQuestStartNode* startNode = NewObject<UQuestStartNode>(questGraph);
	startNode->SetFlags(RF_Transactional);
	startNode->NodePosX = 0;
	startNode->NodePosY = 0;
	questGraph->AddNode(startNode, /*bUserAction=*/ true, /*bSelectNewNode=*/ false);
	startNode->CreateNewGuid();
	startNode->PostPlacedNewNode();
	startNode->AllocateDefaultPins();

	return questAsset;
}
