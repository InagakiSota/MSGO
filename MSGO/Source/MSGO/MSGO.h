// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "Game/StaticDataManager.h"

#define LOCTEXT_NAMESPACE ""

class FMSGOModule : public FDefaultGameModuleImpl
{
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

IMPLEMENT_PRIMARY_GAME_MODULE(FMSGOModule, MSGOModule, "MSGO");

void FMSGOModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings(
			"Project", // ※２
			"MSGO",
			"StaticData",
			LOCTEXT("MySettingName", "StaticData"),
			LOCTEXT("MySettingDescription", "My setting discription"),
			GetMutableDefault<UStaticDataManager>()
		);
	}
}
void FMSGOModule::ShutdownModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings(
			"Project", // ※３
			"MSGO",
			"StaticData"
		);
	}
}