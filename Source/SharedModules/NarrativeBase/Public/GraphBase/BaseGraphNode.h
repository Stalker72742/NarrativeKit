// Created by Stalker7274

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "BaseGraphNode.generated.h"

class UTexture2D;

/**
 * @brief Base graph node. Provides title, description, custom data rows and a pin shape preset
 * (default / branch / switch). Subclass to add quest/dialog specific data and behavior.
 */
UCLASS(Abstract)
class NARRATIVEBASE_API UBaseGraphNode : public UEdGraphNode
{
    GENERATED_BODY()

public:
    UBaseGraphNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    // --- Display fields ---

    /** @brief Title shown at the top of the node. */
    UPROPERTY(EditDefaultsOnly, Category="Display")
    FName NodeTitle {TEXT("Task node")};

    /** @brief Optional description shown in the body. */
    UPROPERTY(EditDefaultsOnly, meta=(MultiLine=true), Category="Display")
    FText NodeDescription;
    
    FLinearColor HeaderColor {FLinearColor(0.18f, 0.42f, 0.78f, 1.0f)};
    
    TSoftObjectPtr<UTexture2D> HeaderIcon;

public:
    // --- Parent class overrides ---
    virtual void AllocateDefaultPins() override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetTooltipText() const override;
    virtual FLinearColor GetNodeTitleColor() const override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    virtual bool CanUserDeleteNode() const override { return true; }
    virtual bool CanDuplicateNode() const override { return true; }
    virtual void PostPasteNode() override;
    virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
#endif

public:
    // --- Const getters ---

    /** @brief Returns the description shown in the body. */
    FORCEINLINE FText GetNodeDescription() const { return NodeDescription; }

    /** @brief Returns the header background color. */
    FORCEINLINE FLinearColor GetHeaderColor() const { return HeaderColor; }

    /** @brief Returns the soft pointer to the header icon. */
    FORCEINLINE TSoftObjectPtr<UTexture2D> GetHeaderIcon() const { return HeaderIcon; }
};
