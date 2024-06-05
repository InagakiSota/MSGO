// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ParameterStructs.h"
#include "CharacterStatusComponent.generated.h"

class AMSGOCharacter;

// ブースト計算用クラス
UCLASS()
class MSGO_API UBoostCalculator : public UObject
{
	GENERATED_BODY()

public:

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MSGO_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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

	// ダッシュ中のフラグ
	bool bIsCurrentDash;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "CharacterStatus")
	FCharacterStatusParameter StatusParameter;


};
