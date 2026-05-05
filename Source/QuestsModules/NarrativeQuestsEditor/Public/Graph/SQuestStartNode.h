// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "Graph/SBaseQuestGraphNode.h"

class UQuestStartNode;

/**
 * @brief Slate widget for the QuestStart node. Override UpdateGraphNode to fully customize visuals.
 */
class NARRATIVEQUESTSEDITOR_API SQuestStartNode : public SBaseQuestGraphNode
{
public:
	SLATE_BEGIN_ARGS(SQuestStartNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UQuestStartNode* InNode);
};
