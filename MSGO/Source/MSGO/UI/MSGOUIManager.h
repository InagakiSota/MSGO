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
	// HUD�E�B�W�F�b�g
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
	// �̗̓Q�[�W�̃Z�b�g�A�b�v
	void SetupHPGauge(const int32 InMaxHP);

	// ���݂̗̑͂��Z�b�g
	void SetNowHP(const int32 InNowHP);

	// �u�[�X�g�Q�[�W�̃Z�b�g�A�b�v
	void SetupBoostGauge(const int32 InMaxBoost);

	// ���݂̃u�[�X�g�e�ʂ��Z�b�g
	void SetNowBoost(const int32 InNowBoost, const bool bIsOverHeat);
	
};
