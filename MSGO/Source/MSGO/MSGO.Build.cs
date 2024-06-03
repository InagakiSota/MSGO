// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MSGO : ModuleRules
{
	public MSGO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HeadMountedDisplay"/*, "MSGO_API"*/ });
		
		// �G�f�B�^��p��UnrealEd���W���[����ǉ�
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		}
		// �p�X�Ƀv���W�F�N�g����ǉ�
		string ProjectName = Target.ProjectFile.GetFileNameWithoutExtension();
		PublicIncludePaths.Add(ProjectName);
	}
}
