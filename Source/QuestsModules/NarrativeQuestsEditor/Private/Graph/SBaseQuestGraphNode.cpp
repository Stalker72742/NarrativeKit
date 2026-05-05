// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/SBaseQuestGraphNode.h"

void SBaseQuestGraphNode::Construct(const FArguments& InArgs, UQuestNodeBase* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}
