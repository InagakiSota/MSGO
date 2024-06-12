// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ParameterStructs.h"
#include "Tickable.h"
#include "CharacterStatusComponent.generated.h"

class AMSGOCharacter;



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
		BeginBoostDash,
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

	// ブーストダッシュ開始
	void BeginBoostDash();
	// ブーストダッシュ終了
	void EndBoostDash();

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

	// Sets default values for this component's properties
	UCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void EndPlay(EEndPlayReason::Type EndPlayReason) override;

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

	// ブーストダッシュの開始
	void BeginBoostDash();
	
	// ブーストダッシュ終了
	void EndBoostDash();

	// オーバーヒートの取得
	UFUNCTION(BlueprintPure)
	bool GetIsOverHeat();

	// 現在のスピードを取得
	const int32 GetNowSpeed();

public:
	FOnOverHeatDelegate OnOverHeatDelegate;

protected:
	// 現在のHP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "現在のHP"))
	int32 NowHP;
	// 最大HP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最大HP"))
	int32 MaxHP;

	// ブースト容量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "現在のブースト容量"))
	int32 NowBoostCap;
	// 最大ブースト容量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最大ブースト容量"))
	int32 MaxBoostCap;

	// ダウンポイント
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "ダウンポイント"))
	int32 NowDownPoint;
	// 最大ダウンポイント
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus", meta = (DisplayName = "最大ダウンポイント"))
	int32 MaxDownPoint;

	// コンポーネント所有者の参照
	UPROPERTY()
	TObjectPtr<AMSGOCharacter> OwnerCharacter;

	// ブースト計算用クラス
	UPROPERTY()
	TObjectPtr<UBoostCalculator> BoostCalculator;

	// 前フレームのブースト容量
	int32 PrevBoostCap;

private:
	// デリゲートを再生したかのフラグ
	bool bIsBroadcastDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "CharacterStatus")
	FCharacterStatusParameter StatusParameter;


};
