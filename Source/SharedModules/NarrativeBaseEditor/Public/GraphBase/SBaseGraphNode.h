// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UBaseGraphNode;
class STextBlock;
class SVerticalBox;
class SImage;
struct FSlateBrush;

/**
 * @brief Slate widget for narrative graph nodes.
 * @note Renders a colored header (from UBaseGraphNode::HeaderColor), an optional icon,
 *       title, description, free-form data rows, and left/right pin columns.
 */
class NARRATIVEBASEEDITOR_API SBaseGraphNode : public SGraphNode
{
public:
    SLATE_BEGIN_ARGS(SBaseGraphNode) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, UBaseGraphNode* InNode);

    // --- Parent class overrides ---

    virtual void UpdateGraphNode() override;
    virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
    virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;

protected:
    // --- Service / helper functions ---

    /** @brief Returns the typed graph node (or nullptr). */
    UBaseGraphNode* GetNarrativeNode() const;

    /** @brief Title text bound from the node. */
    FText GetTitleText() const;

    /** @brief Description text bound from the node. */
    FText GetDescriptionText() const;

    /** @brief Visibility for the description block (collapsed when empty). */
    EVisibility GetDescriptionVisibility() const;

    /** @brief Visibility for the data rows block (collapsed when empty). */
    EVisibility GetDataRowsVisibility() const;

    /** @brief Header background brush color. */
    FSlateColor GetHeaderColor() const;

    /** @brief Returns the loaded header icon brush, or nullptr if unset / not loaded. */
    const FSlateBrush* GetHeaderIconBrush() const;

    /** @brief Visibility for the header icon (collapsed when no icon). */
    EVisibility GetHeaderIconVisibility() const;

    /** @brief (Re)builds the data rows vertical box from the node's DataRows. */
    void RebuildDataRows();

protected:
    // --- Runtime fields ---

    TSharedPtr<SVerticalBox> DataRowsBox;
    TSharedPtr<FSlateBrush> HeaderIconBrush;
};
