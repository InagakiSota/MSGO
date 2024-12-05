// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MSGOGameState.generated.h"

class UMSGOUIManager;
class UAttackCollisionPool;
class AAttackCollision;

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

	UFUNCTION(BlueprintPure,Category = "MSGO|GameState", meta = (DisplayName = "Get MSGO Game State", WorldContext = "WorldContextObject"))
	static class AMSGOGameState* Get(const UObject* WorldContextObject);

	///** Returns the current GameStateBase or Null if it can't be retrieved */
	//UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject"))
	//static ENGINE_API class AGameStateBase* GetGameState(const UObject* WorldContextObject);


public:
	// UIマネージャーの取得
	UFUNCTION(BlueprintCallable)
	UMSGOUIManager* GetUIManager() const
	{
		return UIManager;
	}

	// 攻撃コリジョンプールの取得
	UFUNCTION(BlueprintCallable)
	UAttackCollisionPool* GetAttackCollisionPool() const
	{
		return AttackCollisionPool;
	}

	// 攻撃コリジョンプールから攻撃コリジョンを取得
	UFUNCTION(BlueprintPure)
	AAttackCollision* GetAttackCollisionFromPool();
};
