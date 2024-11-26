// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MSGOUIManager.h"
#include "UI/MyHudWidget.h"
#include "UI/HPGaugeWidget.h"
#include "UI/BoostGaugeWidget.h"
#include "Components/CharacterStatusComponent.h"
#include "Characters/MSGOCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// ゲーム開始時のセットアップ
// @param	InCharacter	操作対象のプレイヤーキャラクター
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

// 体力ゲージのセットアップ
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
// 現在の体力をセット
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

// ブーストゲージのセットアップ
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

// 現在のブースト容量をセット
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

// 体力ゲージの更新
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
