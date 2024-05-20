// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MSGO_MSGOGameMode_generated_h
#error "MSGOGameMode.generated.h already included, missing '#pragma once' in MSGOGameMode.h"
#endif
#define MSGO_MSGOGameMode_generated_h

#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_SPARSE_DATA
#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_RPC_WRAPPERS
#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMSGOGameMode(); \
	friend struct Z_Construct_UClass_AMSGOGameMode_Statics; \
public: \
	DECLARE_CLASS(AMSGOGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/MSGO"), MSGO_API) \
	DECLARE_SERIALIZER(AMSGOGameMode)


#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAMSGOGameMode(); \
	friend struct Z_Construct_UClass_AMSGOGameMode_Statics; \
public: \
	DECLARE_CLASS(AMSGOGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/MSGO"), MSGO_API) \
	DECLARE_SERIALIZER(AMSGOGameMode)


#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	MSGO_API AMSGOGameMode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMSGOGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(MSGO_API, AMSGOGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMSGOGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	MSGO_API AMSGOGameMode(AMSGOGameMode&&); \
	MSGO_API AMSGOGameMode(const AMSGOGameMode&); \
public:


#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	MSGO_API AMSGOGameMode(AMSGOGameMode&&); \
	MSGO_API AMSGOGameMode(const AMSGOGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(MSGO_API, AMSGOGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMSGOGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMSGOGameMode)


#define FID_MSGO_Source_MSGO_MSGOGameMode_h_9_PROLOG
#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_SPARSE_DATA \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_RPC_WRAPPERS \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_INCLASS \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_MSGO_Source_MSGO_MSGOGameMode_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_SPARSE_DATA \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_INCLASS_NO_PURE_DECLS \
	FID_MSGO_Source_MSGO_MSGOGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MSGO_API UClass* StaticClass<class AMSGOGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MSGO_Source_MSGO_MSGOGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
