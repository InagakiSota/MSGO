// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MSGOGameState.generated.h"

class UMSGOUIManager;
class UAttackCollisionPool;

/**
 * 
 */
UCLASS()
class MSGO_API AMSGOGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	// UIマネージャー
	UPROPERTY()
	TObjectPtr<UMSGOUIManager> UIManager;

	// 攻撃コリジョンオブジェクトプール
	UPROPERTY()
	TObjectPtr<UAttackCollisionPool> AttackCollisionPool;

public:

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:
	// UIマネージャーの取得
	UFUNCTION(BlueprintCallable)
	UMSGOUIManager* GetUIManager()
	{
		return UIManager;
	}

	// 攻撃コリジョンプールの取得
	UFUNCTION(BlueprintCallable)
	UAttackCollisionPool* GetAttackCollisionPool()
	{
		return AttackCollisionPool;
	}
	
};
