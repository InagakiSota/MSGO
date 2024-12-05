// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPGaugeWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * HPゲージのウィジェットクラス
 */
UCLASS()
class MSGO_API UHPGaugeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// 最大HPのテキストのセット
	// @param			InMaxHP		最大体力
	UFUNCTION(BlueprintCallable)
	void SetMaxHPText(const int32 InMaxHP);

	// 現在のHPのテキストのセット
	// @param			InNowHP		現在の体力
	UFUNCTION(BlueprintCallable)
	void SetNowHPText(const int32 InNowHP);

public:
	// セットアップ
	// @param			InMaxHP		最大
	UFUNCTION(BlueprintCallable)
	void Setup(const int32 InMaxHP);

	// 現在のHPのセット
	UFUNCTION(BlueprintCallable)
	void SetNowHP(const int32 InNowHP);


protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

public:
	// HPゲージの更新
	void UpdateHPGauge(int32 InNowHP);
	
protected:
	// 最大HPのテキスト
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxHPText;

	// 現在のHPのテキスト
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NowHPText;

	// HPゲージ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HPGauge;

	// 最大HP
	int32 MaxHP;

	// 現在HP
	int32 NowHP;
};
