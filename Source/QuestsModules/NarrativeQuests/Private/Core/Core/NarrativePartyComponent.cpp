// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/QuestsManager/NarrativePartyComponent.h"

UNarrativePartyComponent::UNarrativePartyComponent(const FObjectInitializer& InInitializer) : Super(InInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNarrativePartyComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

