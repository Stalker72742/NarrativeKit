// Created by Stalker7274

#include "Graph/SQuestStartNode.h"
#include "Graph/QuestStartNode.h"

void SQuestStartNode::Construct(const FArguments& InArgs, UQuestStartNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}
