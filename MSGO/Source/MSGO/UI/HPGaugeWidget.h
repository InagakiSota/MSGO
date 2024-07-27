// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPGaugeWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * HP�Q�[�W�̃E�B�W�F�b�g�N���X
 */
UCLASS()
class MSGO_API UHPGaugeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// �ő�HP�̃e�L�X�g�̃Z�b�g
	UFUNCTION(BlueprintCallable)
	void SetMaxHPText(const int32 InMaxHP);

	// ���݂�HP�̃e�L�X�g�̃Z�b�g
	UFUNCTION(BlueprintCallable)
	void SetNowHPText(const int32 InNowHP);

protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;
	
protected:
	// �ő�HP�̃e�L�X�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxHPText;

	// ���݂�HP�̃e�L�X�g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NowHPText;

	// HP�Q�[�W
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HPGauge;
};
