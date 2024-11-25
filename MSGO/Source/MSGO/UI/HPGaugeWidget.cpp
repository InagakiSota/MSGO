// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HPGaugeWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

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

    FText text = FText::FromString(FString::Printf(TEXT("%4d"), InMaxHP));

    MaxHPText->SetText(text);    
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
}

// セットアップ
void UHPGaugeWidget::Setup(const int32 InMaxHP)
{
    SetMaxHPText(InMaxHP);
    SetNowHP(InMaxHP);

    MaxHP = NowHP = InMaxHP;

}

// 現在のHPのセット
void UHPGaugeWidget::SetNowHP(const int32 InNowHP)
{
    SetNowHPText(InNowHP);
    NowHP = InNowHP;

    if (NowHP < 0)
    {
        NowHP = 0;
    }

    //UpdateHPGauge();
}

// HPゲージの更新
void UHPGaugeWidget::UpdateHPGauge(int32 InMaxHP, int32 InNowHP)
{
    if (!HPGauge)
    {
        return;
    }

    SetNowHPText(InNowHP);
    SetMaxHPText(InMaxHP);

    float percent = (float)InNowHP / (float)InMaxHP;

    HPGauge->SetPercent(percent);

    HPGauge->SetFillColorAndOpacity(percent > 0.15 ? FColor(0, 235, 215) : FLinearColor::Red);
}