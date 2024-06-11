// Fill out your copyright notice in the Description page of Project Settings.
// 各種構造体をまとめたやつ
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ParameterStructs.generated.h"

UENUM(BlueprintType)
enum class EBOOST_TYPE : uint8
{
    NORMAL = 0      UMETA(DisplayName = "通常ブースト"),
    HOVER           UMETA(DisplayName = "ホバー"),
    TANK            UMETA(DisplayName = "タンクブースト")
};

// キャラクターのステータスパラメータ構造体
USTRUCT(BlueprintType)
struct FCharacterStatusParameter
{
    GENERATED_USTRUCT_BODY()

public:
    FCharacterStatusParameter();

public:
    // 機体名
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    FName MachineName;

    // 最大HP
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxHP;

    // ブースト容量
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxBoostCap;

    // ブーストチャージ性能
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 BoostCharge;

    // ブーストタイプ
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    TEnumAsByte<EBOOST_TYPE> BoostType;

    // ダウンポイント
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxDownPoint;

    // ブースト初速
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 InitSpeed;

    // 最高速度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxSpeed;
    
    // 巡航速度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 CrusingSpeed;

    // 最高速度移行フレーム
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 TransitionFrame_MaxSpeed;

    // 最高速度維持フレーム
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 SustainedFrame_MaxSpeed;

    // 巡航速度移行フレーム
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 TransitionFrame_CrusingSpeed;

    // 最高歩行速度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxWalkSpeed;
    
    // 最高加速度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxAcceleration;

    // 歩行時最高加速度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MaxWalkAcceleration;

    // 緊急帰投
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 ReturnValue;

    // 機体コスト
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 MachineCost;

    // ダメージカット率　実弾
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    float DamageCutRate_Bullet;

    // ダメージカット率　爆発
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    float DamageCutRate_Bomb;

    // ダメージカット率　ビーム
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    float DamageCutRate_Beam;

    // ダメージカット率　格闘
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    float DamageCutRate_Combat;

    // バトルアシストモジュール　スロット数
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 AssistModuleSlotNum;

    // ジャンプ　上昇高度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 JumpRiseHeight;

    // ジャンプ　上昇速度
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 JumpRiseSpeed;

    // ブースト移動開始時のブーストゲージ減少量
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 BoostGaugeDecrement_BeginBoostDash;

    // ブースト移動時の1フレームあたりのブーストゲージ減少量
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 BoostGaugeDecrement_BoostDash;

    // 通常時の1フレームあたりのブーストゲージの上昇量
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 BoostGaugeIncrement_Normal;

    // オーバーヒート時の1フレームあたりのブーストゲージの上昇量
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 BoostGaugeIncrement_OverHeat;


    // 緊急回避　ブースト消費量
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CharacterStatus")
    int32 BoostGaugeDecrement_Avoidance;
};

// キャラクターのステータスパラメータ構造体(データテーブル用)
USTRUCT()
struct FCharacterStatusParameter_TableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FCharacterStatusParameter_TableRow();

public:
    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "機体ID"))
    int32 MachineID;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最大HP"))
    int32 MaxHP;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ブースト容量"))
    int32 MaxBoostCap;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ブーストチャージ"))
    int32 BoostCharge;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ブーストタイプ"))
    TEnumAsByte<EBOOST_TYPE> BoostType;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ダウンポイント"))
    int32 MaxDownPoint;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ブースト初速"))
    int32 InitSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最高速度"))
    int32 MaxSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "巡航速度"))
    int32 CrusingSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最高速度移行フレーム"))
    int32 TransitionFrame_MaxSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最高速度維持フレーム"))
    int32 SustainedFrame_MaxSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "巡航速度移行フレーム"))
    int32 TransitionFrame_CrusingSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最高歩行速度"))
    int32 MaxWalkSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最高加速度"))
    int32 MaxAcceleration;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "歩行時最高加速度"))
    int32 MaxWalkAcceleration;


    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "緊急帰投"))
    int32 ReturnValue;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "機体コスト"))
    int32 MachineCost;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　実弾"))
    float DamageCutRate_Bullet;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　爆発"))
    float DamageCutRate_Bomb;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　ビーム"))
    float DamageCutRate_Beam;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　格闘"))
    float DamageCutRate_Combat;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "バトルアシストモジュール　スロット数"))
    int32 AssistModuleSlotNum;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ジャンプ　上昇高度"))
    int32 JumpRiseHeight;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ジャンプ　上昇速度"))
    int32 JumpRiseSpeed;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ブースト移動開始時のブーストゲージ減少量"))
    int32 BoostGaugeDecrement_BeginBoostDash;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "ブースト移動時の1フレームあたりのブーストゲージ減少量"))
    int32 BoostGaugeDecrement_BoostDash;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "通常時の1フレームあたりのブーストゲージの上昇量"))
    int32 BoostGaugeIncrement_Normal;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "オーバーヒート時の1フレームあたりのブーストゲージの上昇量"))
    int32 BoostGaugeIncrement_OverHeat;

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "緊急回避　ブースト消費量"))
    int32 BoostGaugeDecrement_Avoidance;
};