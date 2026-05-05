// Created by Stalker7274

#include "Graph/QuestStartNode.h"
#include "EdGraphSchema_K2.h"

UQuestStartNode::UQuestStartNode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UQuestStartNode::AllocateDefaultPins()
{
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

FText UQuestStartNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return NSLOCTEXT("Quest", "QuestStartTitle", "Quest Start");
}

FText UQuestStartNode::GetTooltipText() const
{
    return NSLOCTEXT("Quest", "QuestStartTooltip",
        "Entry point of the quest. Always exists and cannot be deleted.");
}
