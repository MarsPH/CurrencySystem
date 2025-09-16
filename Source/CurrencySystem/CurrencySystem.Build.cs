// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CurrencySystem : ModuleRules
{
	public CurrencySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CurrencySystem",
			"CurrencySystem/Variant_Platforming",
			"CurrencySystem/Variant_Platforming/Animation",
			"CurrencySystem/Variant_Combat",
			"CurrencySystem/Variant_Combat/AI",
			"CurrencySystem/Variant_Combat/Animation",
			"CurrencySystem/Variant_Combat/Gameplay",
			"CurrencySystem/Variant_Combat/Interfaces",
			"CurrencySystem/Variant_Combat/UI",
			"CurrencySystem/Variant_SideScrolling",
			"CurrencySystem/Variant_SideScrolling/AI",
			"CurrencySystem/Variant_SideScrolling/Gameplay",
			"CurrencySystem/Variant_SideScrolling/Interfaces",
			"CurrencySystem/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
