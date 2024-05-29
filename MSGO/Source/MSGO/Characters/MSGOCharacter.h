// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "MSGOCharacter.generated.h"

UCLASS(config=Game)
class AMSGOCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// 歩行時の最高速度
	static const float WALK_SPEED_MAX;
	// ダッシュ時の最高速度
	static const float DASH_SPEED_MAX;

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMSGOCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

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

	// InputAction:視点操作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;

protected:
	// 移動入力値
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	FVector2D MoveInput;

	// ダッシュ中かのフラグ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bIsDash;

	// Yawの回転速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float YawRotSpeed;

	// ダッシュ中の上昇速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float DashRiseSpeed;


protected:
	// 移動処理
	void Move(const FInputActionValue& Value);

	// 移動終了
	void EndMove();

	// 視点操作
	void Look(const FInputActionValue& Value);

	// ダッシュ　入力
	void OnPressDash();
	// ダッシュ　リリース
	void OnReleaseDash();

	// ジャンプ　入力
	void OnPressJump();
	// ジャンプ　リリース
	void OnReleaseJump();
	// ジャンプ　入力中
	void UpdateJump();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// カメラの向いている方に向く
	UFUNCTION(BlueprintCallable)
	void RotToCamera(float InRotSpeed);
};

