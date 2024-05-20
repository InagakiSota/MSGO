// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MSGO/MSGOGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMSGOGameMode() {}
// Cross Module References
	MSGO_API UClass* Z_Construct_UClass_AMSGOGameMode_NoRegister();
	MSGO_API UClass* Z_Construct_UClass_AMSGOGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_MSGO();
// End Cross Module References
	void AMSGOGameMode::StaticRegisterNativesAMSGOGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMSGOGameMode);
	UClass* Z_Construct_UClass_AMSGOGameMode_NoRegister()
	{
		return AMSGOGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AMSGOGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMSGOGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_MSGO,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMSGOGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MSGOGameMode.h" },
		{ "ModuleRelativePath", "MSGOGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMSGOGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMSGOGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMSGOGameMode_Statics::ClassParams = {
		&AMSGOGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AMSGOGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AMSGOGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMSGOGameMode()
	{
		if (!Z_Registration_Info_UClass_AMSGOGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMSGOGameMode.OuterSingleton, Z_Construct_UClass_AMSGOGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMSGOGameMode.OuterSingleton;
	}
	template<> MSGO_API UClass* StaticClass<AMSGOGameMode>()
	{
		return AMSGOGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMSGOGameMode);
	struct Z_CompiledInDeferFile_FID_MSGO_Source_MSGO_MSGOGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MSGO_Source_MSGO_MSGOGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMSGOGameMode, AMSGOGameMode::StaticClass, TEXT("AMSGOGameMode"), &Z_Registration_Info_UClass_AMSGOGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMSGOGameMode), 1909115266U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MSGO_Source_MSGO_MSGOGameMode_h_2268332491(TEXT("/Script/MSGO"),
		Z_CompiledInDeferFile_FID_MSGO_Source_MSGO_MSGOGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MSGO_Source_MSGO_MSGOGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
