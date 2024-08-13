// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MSGOUIManager.h"
#include "UI/MyHudWidget.h"
#include "UI/HPGaugeWidget.h"

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