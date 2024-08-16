// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MSGOUIManager.h"
#include "UI/MyHudWidget.h"
#include "UI/HPGaugeWidget.h"
#include "UI/BoostGaugeWidget.h"

// �̗̓Q�[�W�̃Z�b�g�A�b�v
void UMSGOUIManager::SetupHPGauge(const int32 InMaxHP)
{
    if (!HudWidget)
    {
        return;
    }

    UHPGaugeWidget* hpGauge = HudWidget->GetHPGauge();
    if (!hpGauge)
    {
        return;
    }

    hpGauge->Setup(InMaxHP);
}

// ���݂̗̑͂��Z�b�g
void UMSGOUIManager::SetNowHP(const int32 InNowHP)
{
    if (!HudWidget)
    {
        return;
    }

    UHPGaugeWidget* hpGauge = HudWidget->GetHPGauge();
    if (!hpGauge)
    {
        return;
    }

    hpGauge->SetNowHP(InNowHP);
}

// �u�[�X�g�Q�[�W�̃Z�b�g�A�b�v
void UMSGOUIManager::SetupBoostGauge(const int32 InMaxBoost)
{
    if (!HudWidget)
    {
        return;
    }

    UBoostGaugeWidget* boostGauge = HudWidget->GetBoostGauge();
    if (!boostGauge)
    {
        return;
    }

    boostGauge->Setup(InMaxBoost);
}

// ���݂̃u�[�X�g�e�ʂ��Z�b�g
void UMSGOUIManager::SetNowBoost(const int32 InNowBoost, const bool bIsOverHeat)
{
    if (!HudWidget)
    {
        return;
    }

    UBoostGaugeWidget* boostGauge = HudWidget->GetBoostGauge();
    if (!boostGauge)
    {
        return;
    }

    boostGauge->SetNowBoost(InNowBoost, bIsOverHeat);

}