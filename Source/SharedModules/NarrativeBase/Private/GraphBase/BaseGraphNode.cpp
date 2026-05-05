// Created by Stalker7274

#include "GraphBase/BaseGraphNode.h"
#include "EdGraphSchema_K2.h"

#if WITH_EDITOR
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#endif

UBaseGraphNode::UBaseGraphNode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UBaseGraphNode::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

FText UBaseGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return NodeTitle.ToString().IsEmpty() ? FText::FromString(TEXT("Quest task")) : FText::FromName(NodeTitle);
}

FText UBaseGraphNode::GetTooltipText() const
{
    return NodeDescription.IsEmpty() ? FText::FromString(TEXT("Narrative graph node")) : NodeDescription;
}

FLinearColor UBaseGraphNode::GetNodeTitleColor() const
{
    return HeaderColor;
}

#if WITH_EDITOR
void UBaseGraphNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    const FName name = PropertyChangedEvent.MemberProperty
        ? PropertyChangedEvent.MemberProperty->GetFName()
        : NAME_None;

    if (name == GET_MEMBER_NAME_CHECKED(UBaseGraphNode, NodeTitle) ||
        name == GET_MEMBER_NAME_CHECKED(UBaseGraphNode, NodeDescription) ||
        name == GET_MEMBER_NAME_CHECKED(UBaseGraphNode, HeaderColor) ||
        name == GET_MEMBER_NAME_CHECKED(UBaseGraphNode, HeaderIcon))
    {
        ReconstructNode();
    }
}

void UBaseGraphNode::PostPasteNode()
{
    Super::PostPasteNode();
    CreateNewGuid();
}

void UBaseGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
    if (!Menu || !Context || Context->bIsDebugging)
    {
        return;
    }

    {
        FToolMenuSection& section = Menu->AddSection(
            "NarrativeNodeEdit",
            NSLOCTEXT("NarrativeNode", "EditSection", "Edit"));

        section.AddMenuEntry(FGenericCommands::Get().Delete);
        section.AddMenuEntry(FGenericCommands::Get().Cut);
        section.AddMenuEntry(FGenericCommands::Get().Copy);
        section.AddMenuEntry(FGenericCommands::Get().Duplicate);
    }

    {
        FToolMenuSection& section = Menu->AddSection(
            "NarrativeNodeOrganization",
            NSLOCTEXT("NarrativeNode", "OrganizationSection", "Organization"));

        section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
        section.AddMenuEntry(FGraphEditorCommands::Get().ReconstructNodes);
    }
}
#endif
