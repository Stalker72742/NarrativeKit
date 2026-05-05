// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "Graph/SBaseQuestGraphNode.h"

class UQuestFinishNode;

/**
 * @brief Slate widget for the QuestFinish node. Override UpdateGraphNode to fully customize visuals.
 */
class NARRATIVEQUESTSEDITOR_API SQuestFinishNode : public SBaseQuestGraphNode
{
public:
	SLATE_BEGIN_ARGS(SQuestFinishNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UQuestFinishNode* InNode);
};
