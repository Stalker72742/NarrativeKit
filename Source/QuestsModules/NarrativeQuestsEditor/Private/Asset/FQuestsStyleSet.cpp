// Fill out your copyright notice in the Description page of Project Settings.


#include "Asset/FQuestsStyleSet.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FQuestsStyleSet::StyleSet = nullptr;

void FQuestsStyleSet::Register()
{
	if (StyleSet.IsValid()) return;

	StyleSet = MakeShared<FSlateStyleSet>(FName("QuestsStyleSet"));

	const FString resourcesDir = IPluginManager::Get()
		.FindPlugin(TEXT("NarrativeKit"))->GetBaseDir() / TEXT("Resources");

	StyleSet->SetContentRoot(resourcesDir);
	
	StyleSet->Set(
		"ClassIcon.QuestAsset",
		new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("QuestIcon128"), TEXT(".png")),
			FVector2D(16.f, 16.f)
		)
	);
	
	StyleSet->Set(
		"ClassThumbnail.QuestAsset",
		new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("QuestIcon128"), TEXT(".png")),
			FVector2D(64.f, 64.f)
		)
	);
	
	StyleSet->Set(
		"ClassIcon.Quest",
		new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("QuestIcon128"), TEXT(".png")),
			FVector2D(16.f, 16.f)
		)
	);
	
	StyleSet->Set(
		"ClassThumbnail.Quest",
		new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("QuestIcon128"), TEXT(".png")),
			FVector2D(64.f, 64.f)
		)
	);
	
	StyleSet->Set(
	"ClassIcon.QuestBlueprintGeneratedClass",
		new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("QuestIcon128"), TEXT(".png")),
			FVector2D(16.f, 16.f)
		)
	);

	StyleSet->Set(
		"ClassThumbnail.QuestBlueprintGeneratedClass",
		new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("QuestIcon128"), TEXT(".png")),
			FVector2D(64.f, 64.f)
		)
	);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FQuestsStyleSet::Unregister()
{
	if (!StyleSet.IsValid()) return;

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	StyleSet.Reset();
}

TSharedRef<FSlateStyleSet> FQuestsStyleSet::GetStyleSet()
{
	return StyleSet.ToSharedRef();
}
