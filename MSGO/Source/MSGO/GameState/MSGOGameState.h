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
	// UI�}�l�[�W���[
	UPROPERTY()
	TObjectPtr<UMSGOUIManager> UIManager;

	// �U���R���W�����I�u�W�F�N�g�v�[��
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
	// UI�}�l�[�W���[�̎擾
	UFUNCTION(BlueprintCallable)
	UMSGOUIManager* GetUIManager() const
	{
		return UIManager;
	}

	// �U���R���W�����v�[���̎擾
	UFUNCTION(BlueprintCallable)
	UAttackCollisionPool* GetAttackCollisionPool() const
	{
		return AttackCollisionPool;
	}
	
};
