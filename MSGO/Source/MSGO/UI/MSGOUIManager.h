// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MSGOUIManager.generated.h"

class UMyHudWidget;

/**
 * 
 */
UCLASS()
class MSGO_API UMSGOUIManager : public UObject
{
	GENERATED_BODY()

private:
	// HUDウィジェット
	UPROPERTY()
	TObjectPtr<UMyHudWidget> HudWidget;

public:
	UFUNCTION(BlueprintCallable)
	UMyHudWidget* GetHudWidget()
	{
		return HudWidget;
	}

	UFUNCTION(BlueprintCallable)
	void SetHudWidget(UMyHudWidget* InHudWidget)
	{
		HudWidget = InHudWidget;
	}

public:
	// 体力ゲージのセットアップ
	void SetupHPGauge(const int32 InMaxHP);

	// 現在の体力をセット
	void SetNowHP(const int32 InNowHP);

	// ブーストゲージのセットアップ
	void SetupBoostGauge(const int32 InMaxBoost);

	// 現在のブースト容量をセット
	void SetNowBoost(const int32 InNowBoost, const bool bIsOverHeat);
	
};
