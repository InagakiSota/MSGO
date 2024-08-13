// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HPGaugeWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetSystemLibrary.h"

#define LOCTEXT_NAMESPACE "HPGaugeWidget"

void UHPGaugeWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

bool UHPGaugeWidget::Initialize()
{
    bool succes = Super::Initialize();
    if (!succes)
    {
        return false;
    }
   
    //FText text = FText::FromString("000");
    //MaxHPText->SetText(text);

    //SetMaxHPText(0000);
    //SetNowHPText(0000);

    HPGauge->SetPercent(1.f);

    return true;
}

// 最大HPのテキストをセット
void UHPGaugeWidget::SetMaxHPText(const int32 InMaxHP)
{
    if (!MaxHPText)
    {
        return;
    }

    //FText::F
    FText text = FText::FromString(FString::Printf(TEXT("%4d"), InMaxHP));

    MaxHPText->SetText(text);    
    MaxHP = InMaxHP;
}

// 現在のHPのテキストのセット
void UHPGaugeWidget::SetNowHPText(const int32 InNowHP)
{
    if (!NowHPText)
    {
        return;
    }

    FText text = FText::FromString(FString::Printf(TEXT("%4d"), InNowHP));

    NowHPText->SetText(text);
    NowHP = InNowHP;
}

// セットアップ
void UHPGaugeWidget::Setup(const int32 InMaxHP)
{
    SetMaxHPText(InMaxHP);
    SetNowHP(InMaxHP);

}

// 現在のHPのセット
void UHPGaugeWidget::SetNowHP(const int32 InNowHP)
{
    SetNowHPText(InNowHP);

      UpdateHPGauge();
}

// HPゲージの更新
void UHPGaugeWidget::UpdateHPGauge()
{
    if (!HPGauge)
    {
        return;
    }

    float percent = (float)NowHP / (float)MaxHP;
    UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(percent));
    HPGauge->SetPercent(percent);
}