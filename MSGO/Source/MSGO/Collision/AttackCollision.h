// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Structs/ParameterStructs.h"
#include "AttackCollision.generated.h"

class AMSGOCharacter;

UCLASS()
class MSGO_API AAttackCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// オブジェクトの起動
	// @param		InAttackCollArg		攻撃コリジョンの設定の構造体
	// @param		InStartPos			攻撃コリジョンの初期位置
	// @return							起動出来たらtrueを返す
	UFUNCTION(BlueprintCallable)
	bool WakeObject(const FAttackCollisionParameter& InAttackCollArg, const FAttackCollisionMovementParameter& InMovementArg, AMSGOCharacter* InOwner = nullptr);

	// オブジェクトの停止
	UFUNCTION(BlueprintCallable)
	bool SleepObject();

	// 使用中フラグの取得
	bool GetIsUsing() { return bIsUsing; }

	// 使用者の参照を取得
	AMSGOCharacter* GetOwnerCharacter()
	{
		return OwnerCharacterPtr;
	}

protected:

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* BoxCollision;

	// 使用中かのフラグ
	bool bIsUsing;
	
	// 攻撃コリジョンパラメータ
	FAttackCollisionParameter AttackCollParam;
	// 移動パラメータ
	FAttackCollisionMovementParameter MovementParam;

	// 移動時間
	float MoveTotalSeconds;

	// 使用者の参照
	AMSGOCharacter* OwnerCharacterPtr;
};
