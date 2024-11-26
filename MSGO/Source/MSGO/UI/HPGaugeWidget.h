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

protected:
	// �ő�HP�̃e�L�X�g�̃Z�b�g
	// @param			InMaxHP		�ő�̗�
	UFUNCTION(BlueprintCallable)
	void SetMaxHPText(const int32 InMaxHP);

	// ���݂�HP�̃e�L�X�g�̃Z�b�g
	// @param			InNowHP		���݂̗̑�
	UFUNCTION(BlueprintCallable)
	void SetNowHPText(const int32 InNowHP);

public:
	// �Z�b�g�A�b�v
	// @param			InMaxHP		�ő�
	UFUNCTION(BlueprintCallable)
	void Setup(const int32 InMaxHP);

	// ���݂�HP�̃Z�b�g
	UFUNCTION(BlueprintCallable)
	void SetNowHP(const int32 InNowHP);


protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

public:
	// HP�Q�[�W�̍X�V
	void UpdateHPGauge(int32 InNowHP);
	
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

	// �ő�HP
	int32 MaxHP;

	// ����HP
	int32 NowHP;
};
