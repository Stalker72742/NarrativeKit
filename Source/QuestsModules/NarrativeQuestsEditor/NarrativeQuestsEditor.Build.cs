using UnrealBuildTool;

public class NarrativeQuestsEditor : ModuleRules
{
    public NarrativeQuestsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "NarrativeBaseEditor",
                "NarrativeQuests",
                "UnrealEd",
                "AssetTools",
                "GraphEditor",
                "Slate",
                "SlateCore",
                "ToolMenus",
                "BlueprintGraph",
                "Kismet",
                "KismetWidgets",
                "KismetCompiler"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "PropertyEditor",
                "EditorStyle",
                "EditorFramework",
                "InputCore",
                "Projects"
            }
        );
    }
}
