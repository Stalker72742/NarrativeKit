// Created by Stalker7274

#include "Graph/QuestFinishNode.h"
#include "EdGraphSchema_K2.h"

UQuestFinishNode::UQuestFinishNode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UQuestFinishNode::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
}

FText UQuestFinishNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return bIsSuccess
        ? NSLOCTEXT("Quest", "QuestFinishSuccess", "Finish Quest (Success)")
        : NSLOCTEXT("Quest", "QuestFinishFail",    "Finish Quest (Fail)");
}

FText UQuestFinishNode::GetTooltipText() const
{
    return NSLOCTEXT("Quest", "QuestFinishTooltip",
        "Ends the quest. Toggle bIsSuccess to mark the outcome as success or failure.");
}
