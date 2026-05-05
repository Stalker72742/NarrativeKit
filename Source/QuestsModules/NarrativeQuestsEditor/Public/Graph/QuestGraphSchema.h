// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphBase/BaseGraphSchema.h"
#include "UObject/Object.h"
#include "QuestGraphSchema.generated.h"

/**
 * 
 */
UCLASS()
class NARRATIVEQUESTSEDITOR_API UQuestGraphSchema : public UBaseGraphSchema
{
	GENERATED_BODY()
public:
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override { return EGraphType::GT_Ubergraph; }
	virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;
};
