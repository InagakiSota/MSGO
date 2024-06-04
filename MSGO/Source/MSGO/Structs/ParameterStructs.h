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
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "機体名"))
    FName MachineName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最大HP"))
    int32 MaxHP;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ブースト容量"))
    int32 MaxBoostCap;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ブーストチャージ"))
    int32 BoostCharge;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ブーストタイプ"))
    TEnumAsByte<EBOOST_TYPE> BoostType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ダウンポイント"))
    int32 MaxDownPoint;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最高速度"))
    int32 MaxSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最高歩行速度"))
    int32 MaxWalkSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最高加速度"))
    int32 MaxAcceleration;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "歩行時最高加速度"))
    int32 MaxWalkAcceleration;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "緊急帰投"))
    int32 ReturnValue;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "機体コスト"))
    int32 MachineCost;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　実弾"))
    float DamageCutRate_Bullet;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　爆発"))
    float DamageCutRate_Bomb;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　ビーム"))
    float DamageCutRate_Beam;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ダメージカット率　格闘"))
    float DamageCutRate_Combat;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "バトルアシストモジュール　スロット数"))
    int32 AssistModuleSlotNum;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ジャンプ　上昇高度"))
    int32 JumpRiseHeight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ジャンプ　上昇速度"))
    int32 JumpRiseSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "緊急回避　ブースト消費量"))
    int32 BoostConsumption_Avoidance;
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

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "最高速度"))
    int32 MaxSpeed;

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

    UPROPERTY(EditAnywhere, Category = "CharacterStatus", meta = (DisplayName = "緊急回避　ブースト消費量"))
    int32 BoostConsumption_Avoidance;
};