// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Structs/ParameterStructs.h"
#include "AttackCollision.generated.h"

class AMSGOCharacter;
struct FMachineTeamID;

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
	bool WakeObject(const FAttackParameter& InAttackParam, const FMachineTeamID& InOwnerTeamID);

	// オブジェクトの停止
	UFUNCTION(BlueprintCallable)
	bool SleepObject();

	// 使用中フラグの取得
	bool GetIsUsing() { return bIsUsing; }

	// アクティブかどうかを取得
	bool IsActive() const
	{
		return MoveTotalSeconds > 0.f && bIsUsing;
	}

	// 使用者の参照を取得
	AMSGOCharacter* GetOwnerCharacter()
	{
		return OwnerCharacterPtr;
	}

	// 攻撃力パラメータを取得
	UFUNCTION(BlueprintPure)
	FAttackCollisionPowerParameter GetAttackPowerParameter() const
	{
		return AttackParam.PowerParam;
	}

	// 使用者のチームIDを取得
	UFUNCTION(BlueprintPure)
	FMachineTeamID GetOwnerTeamID() const
	{
		return OwnerTeamID;
	}


protected:

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxCollision;

#if WITH_EDITOR
	//UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
#endif

	// 使用中かのフラグ
	bool bIsUsing;

	// アクティブかのフラグ
	bool bIsActive;

	// 攻撃パラメータ
	FAttackParameter AttackParam;

	// 移動時間
	float MoveTotalSeconds;

	// 使用者の参照
	AMSGOCharacter* OwnerCharacterPtr;

	// 使用者のチームID
	FMachineTeamID OwnerTeamID;
};
