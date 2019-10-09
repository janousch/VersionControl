// Copyright Ramon Janousch. MIT License.

using UnrealBuildTool;

public class VersionControl : ModuleRules
{
	public VersionControl(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
            "Http",
            "Json",
            "JsonUtilities"
        });
	}
}
