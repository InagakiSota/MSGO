﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "MSGOCharacter.generated.h"

// 移動タイプ
UENUM(BlueprintType)
enum class EMOVE_TYPE : uint8
{
	Walk,		// 歩行
	Dash,		// 走行
};

class UCharacterStatusComponent;

UCLASS(config=Game)
class MSGO_API AMSGOCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMSGOCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

public:
	// 機体ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MSGOCharacter", meta = (DisplayName = "機体ID", DisplayPriority = "1"))
	int32 MachineID;

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

	// 移動入力値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	FVector2D MoveInput;

	// 移動タイプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TEnumAsByte<EMOVE_TYPE> MoveType;

	// Yawの回転速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float YawRotSpeed;

	// ダッシュ中の上昇速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float DashRiseSpeed;

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

protected:
	// 移動処理
	void Move(const FInputActionValue& Value);

	// 移動終了
	void EndMove();

	void InputMove(const FVector2D& Input);

	// 視点操作
	void Look(const FInputActionValue& Value);

	// ダッシュ　入力
	void OnPressDash();
	// ダッシュ　リリース
	void OnReleaseDash();
	// ダッシュ　入力中
	void UpdateDash();

	// ジャンプ　入力
	void OnPressJump();
	// ジャンプ　リリース
	void OnReleaseJump();
	// ジャンプ　入力中
	void UpdateJump();

	// ダッシュ終了処理
	void EndDash();
	
	// オーバーヒート時の処理
	void OnOverHeat();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	// キャラクターステータスコンポーネントの取得
	UCharacterStatusComponent* GetCharacterStatusComponent()
	{
		return StatusComponent;
	}

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// カメラの向いている方に向く
	UFUNCTION(BlueprintCallable)
	void RotToCamera(float InRotSpeed);
};
