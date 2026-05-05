using UnrealBuildTool;

public class NarrativeBaseEditor : ModuleRules
{
    public NarrativeBaseEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine",
            "UnrealEd", "GraphEditor", "BlueprintGraph",
            "Slate", "SlateCore",
            "NarrativeBase"
        });
    }
}
