// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MSGO : ModuleRules
{
	public MSGO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HeadMountedDisplay"/*, "MSGO_API"*/ });
		
		// エディタ専用にUnrealEdモジュールを追加
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		}
		// パスにプロジェクト名を追加
		string ProjectName = Target.ProjectFile.GetFileNameWithoutExtension();
		PublicIncludePaths.Add(ProjectName);
	}
}
