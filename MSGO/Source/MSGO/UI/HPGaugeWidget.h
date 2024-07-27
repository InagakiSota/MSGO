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

public:
	// 最大HPのテキストのセット
	UFUNCTION(BlueprintCallable)
	void SetMaxHPText(const int32 InMaxHP);

	// 現在のHPのテキストのセット
	UFUNCTION(BlueprintCallable)
	void SetNowHPText(const int32 InNowHP);

protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;
	
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
};
