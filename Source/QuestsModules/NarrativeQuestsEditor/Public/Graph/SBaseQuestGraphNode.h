// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/QuestNodeBase.h"
#include "GraphBase/SBaseGraphNode.h"

/**
 * 
 */
class NARRATIVEQUESTSEDITOR_API SBaseQuestGraphNode : public SBaseGraphNode
{
public:
	SLATE_BEGIN_ARGS(SBaseQuestGraphNode) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UQuestNodeBase* InNode);
};
