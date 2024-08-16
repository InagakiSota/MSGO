// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BoostGaugeWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#define LOCTEXT_NAMESPACE "BoostGaugeWidget"

void UBoostGaugeWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

bool UBoostGaugeWidget::Initialize()
{
    bool succes = Super::Initialize();
    if (!succes)
    {
        return false;
    }

    return true;
}

// �Z�b�g�A�b�v
// @param			InMaxBoost		���݂̃u�[�X�g�e��
void UBoostGaugeWidget::Setup(const int32 InMaxBoost)
{
    MaxBoostCap = NowBoostCap = InMaxBoost;

    if (!BoostGauge)
    {
        return;
    }
    BoostGauge->SetPercent(1.f);
}

// ���݂̃u�[�X�g�e�ʂ̃Z�b�g
void UBoostGaugeWidget::SetNowBoost(const int32 InNowBoost, const bool bIsOverHeat)
{
    NowBoostCap = InNowBoost;

    UpdateBoostGauge(bIsOverHeat);
}

// �u�[�X�g�Q�[�W�̍X�V
void UBoostGaugeWidget::UpdateBoostGauge(const bool bIsOverHeat)
{
    if (!BoostGauge)
    {
        return;
    }

    float percent = (float)NowBoostCap / (float)MaxBoostCap;
    BoostGauge->SetPercent(percent);

    // �Q�[�W�̐F���Z�b�g
    if (percent > 0.15f && !bIsOverHeat)
    {
        BoostGauge->SetFillColorAndOpacity(FLinearColor::Yellow);
    }
    else
    {
        BoostGauge->SetFillColorAndOpacity(FLinearColor::Red);
    }

}