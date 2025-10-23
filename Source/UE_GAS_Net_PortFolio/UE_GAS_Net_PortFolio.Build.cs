// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_GAS_Net_PortFolio : ModuleRules
{
	public UE_GAS_Net_PortFolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG",
			"AIModule",
			"GameplayTasks",
			"Niagara",
			"NavigationSystem",
			"GameplayAbilities",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"CableComponent"
		});
	}
}
