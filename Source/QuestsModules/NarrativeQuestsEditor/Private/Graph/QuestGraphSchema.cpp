// Created by Stalker7274

#include "Graph/QuestGraphSchema.h"

#include "Graph/QuestNodeBase.h"
#include "Graph/QuestFinishNode.h"

const FPinConnectionResponse UQuestGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	return Super::CanCreateConnection(A, B);
}

template <typename TNodeClass>
struct FQuestNodeSchemaAction_NewNode : public FEdGraphSchemaAction
{
	FQuestNodeSchemaAction_NewNode() : FEdGraphSchemaAction() {}
	FQuestNodeSchemaAction_NewNode(FText InCategory, FText InMenuDesc, FText InToolTip, int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) {}

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
		const FVector2D Location, bool bSelectNewNode = true) override
	{
		TNodeClass* newNode = NewObject<TNodeClass>(ParentGraph);
		newNode->SetFlags(RF_Transactional);
		newNode->NodePosX = Location.X;
		newNode->NodePosY = Location.Y;
		ParentGraph->Modify();
		ParentGraph->AddNode(newNode, true, bSelectNewNode);
		newNode->CreateNewGuid();
		newNode->PostPlacedNewNode();
		newNode->AllocateDefaultPins();

		if (FromPin)
		{
			newNode->AutowireNewNode(FromPin);
		}

		return newNode;
	}
};

void UQuestGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	{
		TSharedPtr<FQuestNodeSchemaAction_NewNode<UQuestNodeBase>> action = MakeShareable(
			new FQuestNodeSchemaAction_NewNode<UQuestNodeBase>(
				FText::FromString("Quest"),
				FText::FromString("Add Quest Node"),
				FText::FromString("Adds a generic quest node"),
				0
			));
		ContextMenuBuilder.AddAction(action);
	}

	{
		TSharedPtr<FQuestNodeSchemaAction_NewNode<UQuestFinishNode>> action = MakeShareable(
			new FQuestNodeSchemaAction_NewNode<UQuestFinishNode>(
				FText::FromString("Quest"),
				FText::FromString("Add Finish Quest"),
				FText::FromString("Adds a node that ends the quest with a success/fail outcome"),
				0
			));
		ContextMenuBuilder.AddAction(action);
	}
}

void UQuestGraphSchema::GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const
{
	DisplayInfo.PlainName   = NSLOCTEXT("Quest", "QuestGraphPlainName", "Quest Graph");
	DisplayInfo.DisplayName = DisplayInfo.PlainName;
	DisplayInfo.Tooltip     = NSLOCTEXT("Quest", "QuestGraphTooltip", "Narrative quest flow graph");
}
