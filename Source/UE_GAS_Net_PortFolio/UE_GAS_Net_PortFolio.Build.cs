// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_GAS_Net_PortFolio : ModuleRules
{
	public UE_GAS_Net_PortFolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.Add(ModuleDirectory);
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","UMG", "AIModule",
            "GameplayTasks","Niagara","NavigationSystem" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "GameplayAbilities", "GameplayTags", "GameplayTasks", "Niagara", "CableComponent" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
