// Fill out your copyright notice in the Description page of Project Settings.
// 各種構造体をまとめたやつ
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/ParameterStructs.h"
#include "CharacterStatusDataAsset.generated.h"

UCLASS()
class MSGO_API UCharacterStatusDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    class UDataTable* DataTable;
#endif

    // キャラクターのステータスデータ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<int, FCharacterStatusParameter> CharacterParameterMap;

public:
    // データ作成用の関数
    UFUNCTION(BlueprintCallable, meta =(CallInEditor = "true"))
    void Build();
};