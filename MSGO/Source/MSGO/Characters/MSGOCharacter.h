﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "../Structs/ParameterStructs.h"

#include "MSGOCharacter.generated.h"

// 移動タイプ
UENUM(BlueprintType)
enum class EMOVE_TYPE : uint8
{
	Walk,		// 歩行
	Dash,		// 走行
};

// ブースト速度のステータス
UENUM()
enum class EBOOST_SPEED_STATUS : uint8
{
	InitSpeed,		// 初速
	MaxSpeed,		// 最高速度
	CrusingSpeed,	// 巡航速度
};

// ジャンプのステータス
UENUM(BlueprintType)
enum class EJUMP_STATUS : uint8
{
	Idle,			// アイドル
	Rising,			// 上昇中
	Hovering,		// ホバリングB
	Falling,		// 落下中
};


class UCharacterStatusComponent;
class AAttackCollision;
class UDamageCollision;

//struct FMachineTeamID;
//struct FAttackCollisionPowerParameter;


UCLASS(config=Game)
class MSGO_API AMSGOCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

public:
	// 機体ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MSGOCharacter", meta = (DisplayName = "機体ID", DisplayPriority = "1"))
	int32 MachineID;

	//// チームID
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MSGOCharacter")
	//TEnumAsByte<ETeamID> TeamId;

	// チームID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MSGOCharacter")
	FMachineTeamID MachineTeamID;

protected:
	// MappingContext
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;
	
	// InputAction:攻撃
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Attack;

	// InputAction:アクション
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Action;
	
	// InputAction:ロックオン
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_LockOn;

	// InputAction:移動
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;

	// InputAction:ダッシュ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Dash;

	// InputAction:しゃがみ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Squat;

	// InputAction:ジャンプ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;

	// InputAction:武器切り替え1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon1;

	// InputAction:武器切り替え2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon2;

	// InputAction:武器切り替え3
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon3;

	// InputAction:武器切り替え 次
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeaponNext;

	// InputAction:武器切り替え　前
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeaponPrev;

	// InputAction:緊急回避
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Avoid;

	// InputAction:視点操作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;

protected:
	// キャラクターステータスのコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	TObjectPtr<UCharacterStatusComponent> StatusComponent;

	// ダメージコリジョンコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DamageCollision")
	TObjectPtr<UDamageCollision> DamageCollision;

	// 移動入力値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_MoveInput, /*Replicated,*/ Category = "Action")
	FVector2D MoveInput;

	// 移動タイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MoveType, Category = "Action")
	EMOVE_TYPE MoveType;

	// Yawの回転速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float YawRotSpeed;

	// ダッシュ中の上昇速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float DashRiseSpeed;

	// ブースト速度のステータス
	EBOOST_SPEED_STATUS NowBoostSpeedStatus;

	// ジャンプのステータス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EJUMP_STATUS NowJumpStatus;


private:
	// 前フレームの移動入力値
	FVector2D PrevMoveInput;

	FVector2D TempMoveInput;

	// 最高速度
	int32 MaxSpeed;
	// 最高歩行速度
	int32 MaxWalkSpeed;
	// 最高加速度
	int32 MaxAcceleration;
	// 歩行時最高加速度
	int32 MaxWalkAcceleration;

	// ブースト移動時のタイマー
	float BoostMoveTimer;
	// ブースト移動のターゲット秒数
	float TargetSeconds;

	// 上昇開始時の高度
	float BeginRiseHeight;

	// キャラの向き用の変数
	//UPROPERTY(ReplicatedUsing = OnRep_MyRotate)
	FRotator MyRotate = FRotator::ZeroRotator;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AAttackCollision> AttackCollision;


public:
	AMSGOCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

/////////////////////////////////////////////////////
// 入力回り
/////////////////////////////////////////////////////

	// 移動処理
	//UFUNCTION(Reliable, Server)
	void OnMove(const FInputActionValue& Value);

	UFUNCTION(Reliable, Server)
	void Server_SetMoveInput(const FVector2D& InValue);
	UFUNCTION(Reliable, NetMulticast)
	void SetMoveInput(const FVector2D& InValue);

	// 移動終了
	void EndMove();

	UFUNCTION(Reliable, Server)
	void InputMoveAndRotation(const FVector2D& Input);

	// 視点操作
	void Look(const FInputActionValue& Value);

	// ダッシュ　入力
	UFUNCTION(Reliable, Server)
	void OnPressDash();
	// ダッシュ　リリース
	UFUNCTION(Reliable, Server)
	void OnReleaseDash();
	// ダッシュ　入力中
	UFUNCTION(Reliable, Server)
	void UpdateDash();

	// ダッシュ開始
	UFUNCTION(Reliable, NetMulticast)
	void BeginDash();
	// ダッシュ終了処理
	UFUNCTION(Reliable, NetMulticast)
	void EndDash();
	// ダッシュ中
	UFUNCTION(Reliable, NetMulticast)
	void OnGoingDash();

	// ジャンプ　入力
	UFUNCTION(Reliable, Server)
	void OnPressJump();
	// ジャンプ　リリース
	UFUNCTION(Reliable, Server)
	void OnReleaseJump();
	// ジャンプ　入力中
	UFUNCTION(Reliable, Server)
	void UpdateJump();

	// ジャンプ終了処理
	UFUNCTION(Reliable, Server)
	void EndJump();

	// オーバーヒート時の処理
	void OnOverHeat();

	// 高度上限かのチェック
	// return		trueなら高度上限
	bool IsHeightLimit();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UFUNCTION()
	void OnRep_MoveInput();

	UFUNCTION()
	void OnRep_MoveType() {};

public:
	// キャラクターステータスコンポーネントの取得
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterStatusComponent* GetCharacterStatusComponent()
	{
		return StatusComponent;
	}

public:
/////////////////////////////////////////////////////
// 移動系
/////////////////////////////////////////////////////

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// カメラの向いている方に向く
	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void RotToCamera(float InRotSpeed);

	UFUNCTION(Reliable, NetMulticast)
	void MovementToInput(FVector InInputDir, float InScaleValue);

	// 移動タイプの取得
	EMOVE_TYPE GetNowMoveType()
	{
		return MoveType;
	}
	// ジャンプ状態の取得
	EJUMP_STATUS GetNowJumpStatus()
	{
		return NowJumpStatus;
	}
	
	// 最高速度を変更する
	UFUNCTION(Reliable, Server)
	void Server_ChangeMaxMoveSpeed(const float& InSpeed);
	UFUNCTION(Reliable, NetMulticast)
	void ChangeMaxMoveSpeed(const float& InSpeed);


/////////////////////////////////////////////////////
// 攻撃系
/////////////////////////////////////////////////////
	// 被弾処理
	void AddDamage(const FAttackCollisionPowerParameter& InAttackPowerParam);

	UFUNCTION(Reliable, Server)
	void OnAttack();


	UFUNCTION(BlueprintImplementableEvent)
	void WakeAttackObject();

};

