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
	// ���s���̍ō����x
	static const float WALK_SPEED_MAX;
	// �_�b�V�����̍ō����x
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
	
	// InputAction:�U��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Attack;

	// InputAction:�A�N�V����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Action;
	
	// InputAction:���b�N�I��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_LockOn;

	// InputAction:�ړ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move;

	// InputAction:�_�b�V��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Dash;

	// InputAction:���Ⴊ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Squat;

	// InputAction:�W�����v
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump;

	// InputAction:����؂�ւ�1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon1;

	// InputAction:����؂�ւ�2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon2;

	// InputAction:����؂�ւ�3
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon3;

	// InputAction:����؂�ւ� ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeaponNext;

	// InputAction:����؂�ւ��@�O
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeaponPrev;

	// InputAction:���_����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Look;

protected:
	// �ړ����͒l
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
	FVector2D MoveInput;

	// �_�b�V�������̃t���O
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bIsDash;

	// Yaw�̉�]���x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float YawRotSpeed;

	// �_�b�V�����̏㏸���x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	float DashRiseSpeed;


protected:
	// �ړ�����
	void Move(const FInputActionValue& Value);

	// �ړ��I��
	void EndMove();

	// ���_����
	void Look(const FInputActionValue& Value);

	// �_�b�V���@����
	void OnPressDash();
	// �_�b�V���@�����[�X
	void OnReleaseDash();

	// �W�����v�@����
	void OnPressJump();
	// �W�����v�@�����[�X
	void OnReleaseJump();
	// �W�����v�@���͒�
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

	// �J�����̌����Ă�����Ɍ���
	UFUNCTION(BlueprintCallable)
	void RotToCamera(float InRotSpeed);
};

