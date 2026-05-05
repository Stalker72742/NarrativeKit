// Created by Stalker7274

#include "GraphBase/SBaseGraphNode.h"
#include "GraphBase/BaseGraphNode.h"
#include "NodeFactory.h"
#include "SGraphPin.h"
#include "KismetPins/SGraphPinExec.h"
#include "EdGraphSchema_K2.h"
#include "EdGraph/EdGraphPin.h"
#include "Engine/Texture2D.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateBrush.h"
#include "Styling/StyleDefaults.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"

void SBaseGraphNode::Construct(const FArguments& InArgs, UBaseGraphNode* InNode)
{
    GraphNode = InNode;
    UpdateGraphNode();
}

void SBaseGraphNode::UpdateGraphNode()
{
    InputPins.Empty();
    OutputPins.Empty();
    RightNodeBox.Reset();
    LeftNodeBox.Reset();
    DataRowsBox.Reset();
    HeaderIconBrush.Reset();

    if (UBaseGraphNode* node = GetNarrativeNode())
    {
        if (UTexture2D* iconTexture = node->GetHeaderIcon().LoadSynchronous())
        {
            HeaderIconBrush = MakeShared<FSlateBrush>();
            HeaderIconBrush->SetResourceObject(iconTexture);
            HeaderIconBrush->ImageSize = FVector2D(16.f, 16.f);
            HeaderIconBrush->DrawAs = ESlateBrushDrawType::Image;
        }
    }

    ContentScale.Bind(this, &SGraphNode::GetContentScale);

    GetOrAddSlot(ENodeZone::Center)
    .HAlign(HAlign_Fill)
    .VAlign(VAlign_Center)
    [
        SNew(SBorder)
        .BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
        .Padding(0.f)
        [
            SNew(SVerticalBox)

            // === Header ===
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SBorder)
                .BorderImage(FAppStyle::GetBrush("Graph.Node.ColorSpill"))
                .BorderBackgroundColor(this, &SBaseGraphNode::GetHeaderColor)
                .Padding(FMargin(10.f, 6.f))
                [
                    SNew(SHorizontalBox)

                    // Icon
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    .Padding(FMargin(0.f, 0.f, 6.f, 0.f))
                    [
                        SNew(SBox)
                        .WidthOverride(18.f)
                        .HeightOverride(18.f)
                        .Visibility(this, &SBaseGraphNode::GetHeaderIconVisibility)
                        [
                            SNew(SImage)
                            .Image(this, &SBaseGraphNode::GetHeaderIconBrush)
                        ]
                    ]

                    // Title
                    + SHorizontalBox::Slot()
                    .FillWidth(1.f)
                    .VAlign(VAlign_Center)
                    [
                        SNew(STextBlock)
                        .Text(this, &SBaseGraphNode::GetTitleText)
                        .Font(FAppStyle::GetFontStyle("Graph.Node.NodeTitle"))
                        .ColorAndOpacity(FLinearColor::White)
                    ]
                ]
            ]

            // === Body row: [Input pins] [Body content] [Output pins] ===
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SBorder)
                .BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
                .Padding(FMargin(0.f, 6.f, 0.f, 6.f))
                [
                    SNew(SHorizontalBox)

                    // Left: input pins column
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Top)
                    .Padding(FMargin(7.f, 0.f, 6.f, 0.f))
                    [
                        SAssignNew(LeftNodeBox, SVerticalBox)
                    ]

                    // Center: body content (description + data rows)
                    + SHorizontalBox::Slot()
                    .FillWidth(1.f)
                    .VAlign(VAlign_Top)
                    .Padding(FMargin(6.f, 2.f, 6.f, 2.f))
                    [
                        SNew(SVerticalBox)

                        // Description
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(FMargin(0.f, 0.f, 0.f, 2.f))
                        [
                            SNew(STextBlock)
                            .Text(this, &SBaseGraphNode::GetDescriptionText)
                            .Visibility(this, &SBaseGraphNode::GetDescriptionVisibility)
                            .ColorAndOpacity(FLinearColor(0.85f, 0.85f, 0.85f))
                            .AutoWrapText(true)
                            .WrapTextAt(220.f)
                        ]

                        // Data rows
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        [
                            SAssignNew(DataRowsBox, SVerticalBox)
                            .Visibility(this, &SBaseGraphNode::GetDataRowsVisibility)
                        ]
                    ]

                    // Right: output pins column
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Top)
                    .Padding(FMargin(6.f, 0.f, 7.f, 0.f))
                    [
                        SAssignNew(RightNodeBox, SVerticalBox)
                    ]
                ]
            ]
        ]
    ];

    RebuildDataRows();
    CreatePinWidgets();
}

TSharedPtr<SGraphPin> SBaseGraphNode::CreatePinWidget(UEdGraphPin* Pin) const
{
    if (Pin && Pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec)
    {
        auto pinWidget = SNew(SGraphPinExec, Pin);
        pinWidget.Get().SetShowLabel(false);
        return pinWidget;
    }
    return SGraphNode::CreatePinWidget(Pin);
}

void SBaseGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
    PinToAdd->SetOwner(SharedThis(this));
    if (PinToAdd->GetDirection() == EGPD_Input)
    {
        LeftNodeBox->AddSlot()
            .AutoHeight()
            .HAlign(HAlign_Left)
            .VAlign(VAlign_Center)
            .Padding(FMargin(0.f, 2.f))
            [
                PinToAdd
            ];
        InputPins.Add(PinToAdd);
    }
    else
    {
        RightNodeBox->AddSlot()
            .AutoHeight()
            .HAlign(HAlign_Right)
            .VAlign(VAlign_Center)
            .Padding(FMargin(0.f, 2.f))
            [
                PinToAdd
            ];
        OutputPins.Add(PinToAdd);
    }
}

UBaseGraphNode* SBaseGraphNode::GetNarrativeNode() const
{
    return Cast<UBaseGraphNode>(GraphNode);
}

FText SBaseGraphNode::GetTitleText() const
{
    if (UBaseGraphNode* node = GetNarrativeNode())
    {
        return node->GetNodeTitle(ENodeTitleType::FullTitle);
    }
    return FText::GetEmpty();
}

FText SBaseGraphNode::GetDescriptionText() const
{
    UBaseGraphNode* node = GetNarrativeNode();
    return node ? node->GetNodeDescription() : FText::GetEmpty();
}

EVisibility SBaseGraphNode::GetDescriptionVisibility() const
{
    UBaseGraphNode* node = GetNarrativeNode();
    return (node && !node->GetNodeDescription().IsEmptyOrWhitespace())
        ? EVisibility::Visible
        : EVisibility::Collapsed;
}

EVisibility SBaseGraphNode::GetDataRowsVisibility() const
{
    return EVisibility::Collapsed;
}

FSlateColor SBaseGraphNode::GetHeaderColor() const
{
    UBaseGraphNode* node = GetNarrativeNode();
    return FSlateColor(node ? node->GetHeaderColor() : FLinearColor(0.18f, 0.42f, 0.78f));
}

const FSlateBrush* SBaseGraphNode::GetHeaderIconBrush() const
{
    return HeaderIconBrush.IsValid() ? HeaderIconBrush.Get() : FStyleDefaults::GetNoBrush();
}

EVisibility SBaseGraphNode::GetHeaderIconVisibility() const
{
    return HeaderIconBrush.IsValid() ? EVisibility::Visible : EVisibility::Collapsed;
}

void SBaseGraphNode::RebuildDataRows()
{
}