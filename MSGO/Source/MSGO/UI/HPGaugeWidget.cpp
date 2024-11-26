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

    HPGauge->SetPercent(1.f);

    return true;
}

// �ő�HP�̃e�L�X�g���Z�b�g
void UHPGaugeWidget::SetMaxHPText(const int32 InMaxHP)
{
    if (!MaxHPText)
    {
        return;
    }

    FText text = FText::FromString(FString::Printf(TEXT("%4d"), InMaxHP));

    MaxHPText->SetText(text);    
}

// ���݂�HP�̃e�L�X�g�̃Z�b�g
void UHPGaugeWidget::SetNowHPText(const int32 InNowHP)
{
    if (!NowHPText)
    {
        return;
    }

    FText text = FText::FromString(FString::Printf(TEXT("%4d"), InNowHP));

    NowHPText->SetText(text);
}

// �Z�b�g�A�b�v
void UHPGaugeWidget::Setup(const int32 InMaxHP)
{
    SetMaxHPText(InMaxHP);
    SetNowHP(InMaxHP);

    MaxHP = NowHP = InMaxHP;
    UpdateHPGauge(MaxHP);
}

// ���݂�HP�̃Z�b�g
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

// HP�Q�[�W�̍X�V
void UHPGaugeWidget::UpdateHPGauge(int32 InNowHP)
{
    if (!HPGauge)
    {
        return;
    }

    SetNowHPText(InNowHP);
    SetMaxHPText(MaxHP);

    NowHP = InNowHP;
    if (NowHP < 0)
    {
        NowHP = 0;
    }

    float percent = (float)InNowHP / (float)MaxHP;

    HPGauge->SetPercent(percent);

    HPGauge->SetFillColorAndOpacity(percent > 0.15 ? FColor(0, 235, 215) : FLinearColor::Red);
}