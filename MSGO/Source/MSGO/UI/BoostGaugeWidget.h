// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoostGaugeWidget.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * ブーストゲージのウィジェットクラス
 */
UCLASS()
class MSGO_API UBoostGaugeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

public:
	// セットアップ
	// @param			InMaxBoost		現在のブースト容量
	UFUNCTION(BlueprintCallable)
	void Setup(const int32 InMaxBoost);

	// 現在のブースト容量のセット
	UFUNCTION(BlueprintCallable)
	void SetNowBoost(const int32 InNowBoost, const bool bIsOverHeat);


protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

	// ブーストゲージの更新
	void UpdateBoostGauge(const bool bIsOverHeat);

protected:
	//// 最大HPのテキスト
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<UTextBlock> MaxHPText;

	//// 現在のHPのテキスト
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<UTextBlock> NowHPText;

	// ブーストゲージ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> BoostGauge;

	// 最大ブースト容量
	int32 MaxBoostCap;

	// 現在ブースト容量
	int32 NowBoostCap;
	
};
