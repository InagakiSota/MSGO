// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "AttackCollisionPool.generated.h"

class AAttackCollision;

/**
 * 
 */
UCLASS()
class MSGO_API UAttackCollisionPool : public UObject
{
	GENERATED_BODY()

public:
	// オブジェクトプールの最大数
	static const int32 AttackCollisionPoolNum;

public:
	// 攻撃コリジョンの配列
	UPROPERTY()
	TArray<TObjectPtr<AAttackCollision>> AttackCollisions;

public:
	// ゲーム開始時処理
	void BeginPlay();

	// ゲーム終了時処理
	void BeginDestroy();

};
