// Created by Stalker7274

#include "Graph/SQuestFinishNode.h"
#include "Graph/QuestFinishNode.h"

void SQuestFinishNode::Construct(const FArguments& InArgs, UQuestFinishNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}
