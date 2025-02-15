﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ParameterStructs.h"
#include "Tickable.h"
#include "CharacterStatusComponent.generated.h"

class AMSGOCharacter;
class UMSGOUIManager;

// ブースト計算用クラス
UCLASS()
class MSGO_API UBoostCalculator : public UObject,public FTickableGameObject
{
	GENERATED_BODY()

public:

	// ブーストの状態
	enum class EBOOST_STATE : uint8
	{
		None		 = 0,
		BeginBoostIgnition,
		OverHeat,
	};

	UBoostCalculator();

	// FTickableGameObjectからオーバーライド
	virtual TStatId GetStatId() const;
	virtual bool IsTickable() const { return(true); }
	virtual void Tick(float DeltaTime);

	ETickableTickType GetTickableTickType() const
	{
		return IsTemplate() ? ETickableTickType::Never : ETickableTickType::Always;
	}

public:
	// 現在のブースト容量の計算
	void CalcNowBoostCap(float DeltaTime);

	// 現在のブースト容量の取得
	const int32 GetNowBoostCap()
	{
		return NowBoostCap;
	}

	// 現在のスピードの取得
	const int32 GetNowBoostSpeed()
	{
		return NowBoostSpeed;
	}

	// ブースト消費開始
	void BeginBoost();
	// ブースト消費終了
	void EndBoost();

	// ブースト消費開始　ダッシュ
	void BeginBoost_Dash();
	// ブースト終了処理　ダッシュ
	void EndBoost_Dash();

	// ブースト消費開始 ジャンプ
	void BeginBoost_Jump();
	// ブースト消費終了　ジャンプ
	void EndBoost_Jump();


	// 所有者のセット
	void SetOwnerCharacter(AMSGOCharacter* InOwnerCharacter)
	{
		OwnerCharacter = InOwnerCharacter;
	}

	// ステータスパラメータの取得
	void SetupStatusParam(const FCharacterStatusParameter& InStatusParam);

	// オーバーヒートフラグの取得
	const bool GetIsOverHeat()
	{
		return NowBoostState == EBOOST_STATE::OverHeat;
	}

private:
	// 現在のブーストの状態
	EBOOST_STATE NowBoostState;

	// 現在のブースト容量
	int32 NowBoostCap;

	// 1フレーム前のブースト容量
	int32 PrevBoostCap;

	// 現在のスピード
	int32 NowBoostSpeed;

	// 所有者の参照
	UPROPERTY()
	TObjectPtr<AMSGOCharacter> OwnerCharacter;

	// 現在のブースト消費量
	uint32 BoostDecrementValue;

	// ステータスパラメータ
	// MEMO:ここで持っていていいかは考え中
	FCharacterStatusParameter StatusParam;

	// オーバーヒート時にブースト回復が開始する用のタイマー
	float BeginChargeTimerWithOverHeat;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MSGO_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	DECLARE_MULTICAST_DELEGATE(FOnOverHeatDelegate);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeHPDelegate, const int32);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetupHPDelegate, const int32);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangeBoostDelegate, const int32, const bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetupBoostDelegate, const int32);

	// Sets default values for this component's properties
	UCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ステータスパラメータの取得
	UFUNCTION(BlueprintCallable)
	FCharacterStatusParameter GetStatusParameter()
	{
		return StatusParameter;
	}

	// 所有者の取得
	UFUNCTION(BlueprintCallable)
	AMSGOCharacter* GetOwnerCharacter()
	{
		return OwnerCharacter;
	}

	// パラメータのセットアップ
	// @param			InMachineID		機体ID
	void SetupParameter(int32 InMachineID);

	// ブースト消費の開始
	void BeginBoost();
	
	// ブースト消費終了
	void EndBoost();

	// ブースト消費開始　ダッシュ
	void BeginBoost_Dash();
	// ブースト終了処理　ダッシュ
	void EndBoost_Dash();

	// ブースト消費開始 ジャンプ
	void BeginBoost_Jump();
	// ブースト消費終了　ジャンプ
	void EndBoost_Jump();

	// オーバーヒートの取得
	UFUNCTION(BlueprintPure)
	bool GetIsOverHeat();

	// 現在のスピードを取得
	const int32 GetNowSpeed();

	// 被弾処理
	void AddDamage(const FAttackCollisionPowerParameter& InAttackPowerParam);


	void OnSetupDelegateBind();

public:
	UFUNCTION(BlueprintCallable)
	void SetNowHP(const float& InHP);

	UFUNCTION(Server, Reliable)
	void Server_SetNowHP(const float& InHP);

	UFUNCTION()
	void OnRep_NowHP();

private:
	void CreateBoostCalculator();


public:
	// オーバーヒート時のデリゲート
	FOnOverHeatDelegate OnOverHeatDelegate;

	// HP初期化時のデリゲート
	FOnSetupHPDelegate OnSetupHPDelegate;
	// HP変更時のデリゲート
	FOnChangeHPDelegate OnChangeHPDelegate;
	// ブースト初期化時のデリゲート
	FOnSetupBoostDelegate OnSetupBoostDelegate;
	// ブースト変更時のデリゲート
	FOnChangeBoostDelegate OnChangeBoostDelegate;

protected:
	// 現在のHP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus", ReplicatedUsing = OnRep_NowHP)
	float NowHP;
	// 最大HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	float MaxHP;

	// ブースト容量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	float NowBoostCap;
	// 最大ブースト容量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	float MaxBoostCap;

	// ダウンポイント
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	float NowDownPoint;
	// 最大ダウンポイント
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	float MaxDownPoint;

	// コンポーネント所有者の参照
	UPROPERTY()
	TObjectPtr<AMSGOCharacter> OwnerCharacter;

	// ブースト計算用クラス
	UPROPERTY()
	TObjectPtr<UBoostCalculator> BoostCalculator;

	// 前フレームのブースト容量
	int32 PrevBoostCap;

private:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "CharacterStatus")
	FCharacterStatusParameter StatusParameter;


};
