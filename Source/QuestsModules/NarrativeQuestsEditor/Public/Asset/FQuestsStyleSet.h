// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FQuestsStyleSet
{
public:
	static void Register();
	static void Unregister();

	static TSharedRef<FSlateStyleSet> GetStyleSet();

private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};
