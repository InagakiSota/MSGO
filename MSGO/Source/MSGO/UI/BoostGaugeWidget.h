// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoostGaugeWidget.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * �u�[�X�g�Q�[�W�̃E�B�W�F�b�g�N���X
 */
UCLASS()
class MSGO_API UBoostGaugeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

public:
	// �Z�b�g�A�b�v
	// @param			InMaxBoost		���݂̃u�[�X�g�e��
	UFUNCTION(BlueprintCallable)
	void Setup(const int32 InMaxBoost);

	// ���݂̃u�[�X�g�e�ʂ̃Z�b�g
	UFUNCTION(BlueprintCallable)
	void SetNowBoost(const int32 InNowBoost, const bool bIsOverHeat);


protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

	// �u�[�X�g�Q�[�W�̍X�V
	void UpdateBoostGauge(const bool bIsOverHeat);

protected:
	//// �ő�HP�̃e�L�X�g
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<UTextBlock> MaxHPText;

	//// ���݂�HP�̃e�L�X�g
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	//TObjectPtr<UTextBlock> NowHPText;

	// �u�[�X�g�Q�[�W
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> BoostGauge;

	// �ő�u�[�X�g�e��
	int32 MaxBoostCap;

	// ���݃u�[�X�g�e��
	int32 NowBoostCap;
	
};
