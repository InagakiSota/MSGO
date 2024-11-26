// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MSGOUIManager.h"
#include "UI/MyHudWidget.h"
#include "UI/HPGaugeWidget.h"
#include "UI/BoostGaugeWidget.h"
#include "Components/CharacterStatusComponent.h"
#include "Characters/MSGOCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// �Q�[���J�n���̃Z�b�g�A�b�v
// @param	InCharacter	����Ώۂ̃v���C���[�L�����N�^�[
void UMSGOUIManager::SetupOnBeginPlay(AMSGOCharacter* InCharacter)
{
    if (!InCharacter)
    {
        return;
    }

    PlayerCharacter = InCharacter;

    UCharacterStatusComponent* statusComponent = PlayerCharacter->GetCharacterStatusComponent();
    if (!statusComponent)
    {
        return;
    }

    statusComponent->OnChangeHPDelegate.AddUObject(this, &UMSGOUIManager::UpdateHPGauge);
    statusComponent->OnSetupHPDelegate.AddUObject(this, &UMSGOUIManager::SetupHPGauge);
    statusComponent->OnChangeBoostDelegate.AddUObject(this, &UMSGOUIManager::SetNowBoost);
    statusComponent->OnSetupBoostDelegate.AddUObject(this, &UMSGOUIManager::SetupBoostGauge);
}

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

#if 0
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
#endif

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

// �̗̓Q�[�W�̍X�V
void UMSGOUIManager::UpdateHPGauge(const int32 InNowHP)
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

    hpGauge->UpdateHPGauge(InNowHP);


}
