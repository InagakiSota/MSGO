// Fill out your copyright notice in the Description page of Project Settings.

//
#include "DataAssets/CharacterStatusDataAsset.h"

#if WITH_EDITOR
#include "Misc/MessageDialog.h"
#include "UObject/Package.h"
#include "EditorReimportHandler.h"
#include "FileHelpers.h"
#endif

#define LOCTEXT_NAMESPACE "TEST"

void UCharacterStatusDataAsset::Build()
{
#if WITH_EDITORONLY_DATA

    // データテーブルの設定をチェック
    if (!DataTable)
    {
        const FText TitleText = LOCTEXT("Title", "WarningMessage");
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("MEssage", "DAtaTable is Null"), &TitleText);
        return;
    }

    // データテーブルの型チェック
    if (!DataTable->GetRowStruct()->IsChildOf(FCharacterStatusParameter_TableRow::StaticStruct()))
    {
        const FText TitleText = LOCTEXT("Title", "WarningMassege");
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Message", "DataTable type does not match"), &TitleText);
        return;
    }

    TArray<UPackage*> PackagesToSave;

    // データテーブルをリインポート
    if (FReimportManager::Instance()->Reimport(DataTable, false, true))
    {
        PackagesToSave.Add(DataTable->GetOutermost());
    }

    CharacterParameterMap.Empty();

    // データテーブルの業の要素を配列で取得
    TArray RowNames = DataTable->GetRowNames();
    // 行の数だけループ
    for (auto RowName : RowNames)
    {
        // 一行分の構造体を取得
        FCharacterStatusParameter_TableRow* TableRow = DataTable->FindRow<FCharacterStatusParameter_TableRow>(RowName, FString());

        // ゲーム上で使える形にする
        FCharacterStatusParameter CharacterParameter;
        CharacterParameter.MachineName = RowName;
        CharacterParameter.MaxSpeed                 = TableRow->MaxSpeed;
        CharacterParameter.MaxBoostCap              = TableRow->MaxBoostCap;
        CharacterParameter.BoostCharge              = TableRow->BoostCharge;
        CharacterParameter.MaxDownPoint             = TableRow->MaxDownPoint;
        CharacterParameter.MaxAcceleration          = TableRow->MaxAcceleration;
        CharacterParameter.ReturnValue              = TableRow->ReturnValue;
        CharacterParameter.MachineCost              = TableRow->MachineCost;
        CharacterParameter.DamageCutRate_Bullet     = TableRow->DamageCutRate_Bullet;
        CharacterParameter.DamageCutRate_Bomb       = TableRow->DamageCutRate_Bomb;
        CharacterParameter.DamageCutRate_Beam       = TableRow->DamageCutRate_Beam;
        CharacterParameter.DamageCutRate_Combat     = TableRow->DamageCutRate_Combat;
        CharacterParameter.AssistModuleSlotNum      = TableRow->AssistModuleSlotNum;
        CharacterParameter.JumpRiseHeight           = TableRow->JumpRiseHeight;
        CharacterParameter.JumpRiseSpeed            = TableRow->JumpRiseSpeed;
        CharacterParameter.BoostConsumption_Avoidance = TableRow->BoostConsumption_Avoidance;

        // Mapに追加する
        CharacterParameterMap.Add(TableRow->MachineID, CharacterParameter);

    }

    // データアセットに編集フラグを追加
    MarkPackageDirty();

    // データアセットを保存対象に追加
    PackagesToSave.Add(GetOutermost());

    FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, true, true);

#endif
}

#undef LOCTEXT_NAMESPACE