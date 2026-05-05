// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NarrativePartyComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class NARRATIVEQUESTS_API UNarrativePartyComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	
	UNarrativePartyComponent(const FObjectInitializer& InInitializer);

public:

	virtual void BeginPlay() override;
};
