﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "MSGOCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CharacterStatusComponent.h"
#include "Structs/ParameterStructs.h"

//////////////////////////////////////////////////////////////////////////
// AMSGOCharacter


AMSGOCharacter::AMSGOCharacter()
{
	// ステータスコンポーネントをアタッチ
	StatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("CharacterStatusComponent"));


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	MoveType = EMOVE_TYPE::Walk;

	YawRotSpeed = 10.f;
	DashRiseSpeed = 1.f;

	PrevMoveInput = TempMoveInput = FVector2D(0.0f,0.0f);

	
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(StatusComponent->GetStatusParameter().MaxSpeed));
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMSGOCharacter::BeginPlay()
{
	Super::BeginPlay();

	//UKismetSystemLibrary::PrintString(this, "MSGOCharacter:BeginPlay");

	StatusComponent->SetupParameter(MachineID);
	
	// オーバーヒート時の処理をバインド
	StatusComponent->OnOverHeatDelegate.AddUObject(this, &AMSGOCharacter::OnOverHeat);

	// ステータスコンポーネントから速度を取得してくる
	FCharacterStatusParameter statusParam = StatusComponent->GetStatusParameter();

	MaxSpeed = statusParam.MaxSpeed;
	MaxWalkSpeed = statusParam.MaxWalkSpeed;
	MaxAcceleration = statusParam.MaxAcceleration;
	MaxWalkAcceleration = statusParam.MaxWalkAcceleration;

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MaxAcceleration = MaxWalkAcceleration;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

}

//////////////////////////////////////////////////////////////////////////
// Input

void AMSGOCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 移動
		enhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMSGOCharacter::Move);
		enhancedInput->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMSGOCharacter::EndMove);

		// 攻撃
		//enhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMSGOCharacter::);

		// 視点操作
		enhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMSGOCharacter::Look);

		// ダッシュ
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Started, this, &AMSGOCharacter::OnPressDash);
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AMSGOCharacter::OnReleaseDash);
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Triggered, this, &AMSGOCharacter::UpdateDash);

		// ジャンプ
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMSGOCharacter::OnPressJump);
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AMSGOCharacter::OnReleaseJump);
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMSGOCharacter::UpdateJump);

	}
}

// 移動処理
void AMSGOCharacter::Move(const FInputActionValue& Value)
{
	MoveInput = Value.Get<FVector2D>();

	if ((Controller != nullptr) && (MoveInput.Length() > 0.0f))
	{	
		InputMove(MoveInput);
	}
}

// 移動終了
void AMSGOCharacter::EndMove()
{
	MoveInput = FVector2D(0, 0);

	if (MoveType == EMOVE_TYPE::Dash)
	{
		//OnReleaseDash();
	}
}

void AMSGOCharacter::InputMove(const FVector2D& Input)
{
	FVector2D inputTemp = Input;

	RotToCamera(YawRotSpeed);

	inputTemp.Normalize();
	FVector2D inputDir = inputTemp.GetRotated(Controller->GetControlRotation().Yaw);

	AddMovementInput(FVector(inputDir.X, inputDir.Y, 0.0), 1.0);

}

// ダッシュ　入力
void AMSGOCharacter::OnPressDash()
{
	// オーバーヒート中は処理しない
	if (StatusComponent->GetIsOverHeat())
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	GetCharacterMovement()->MaxFlySpeed = MaxSpeed;
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
	GetCharacterMovement()->GravityScale = 0.0;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	// 移動タイプをダッシュにする
	MoveType = EMOVE_TYPE::Dash;

	StatusComponent->BeginBoostDash();

}

// ダッシュ　リリース
void AMSGOCharacter::OnReleaseDash()
{
	if (StatusComponent->GetIsOverHeat())
	{
		return;
	}

	EndDash();
}

// ダッシュ 入力中
void AMSGOCharacter::UpdateDash()
{
	// オーバーヒート中は処理しない
	if (StatusComponent->GetIsOverHeat() || MoveType != EMOVE_TYPE::Dash)
	{
		return;
	}

	if (MoveInput.Length() <= 0.0f)
	{
		InputMove(FVector2D(1.0f, 0.0f));
	}

}

// ジャンプ　入力
void AMSGOCharacter::OnPressJump()
{
	if (MoveType == EMOVE_TYPE::Walk)
	{
		Jump();
	}
	
}
// ジャンプ　リリース
void AMSGOCharacter::OnReleaseJump()
{
	if (MoveType == EMOVE_TYPE::Walk)
	{
		StopJumping();

		GetCharacterMovement()->GravityScale = 1.0f;
	}
	
}
// ジャンプ　入力中
void AMSGOCharacter::UpdateJump()
{
	// オーバーヒート中は処理しない
	if (StatusComponent->GetIsOverHeat())
	{
		return;
	}

	// 落下時にジャンプボタンを推している場合はホバリングする
	if (MoveType == EMOVE_TYPE::Walk)
	{
		FVector velocity = GetCharacterMovement()->Velocity;

		if (velocity.Z < 0)
		{
			GetCharacterMovement()->GravityScale = 0.1;
		}
	
	}
	// ダッシュ中はジャンプじゃなく上昇させる
	else
	{
		FVector actorPos = FVector(0.0, 0.0, DashRiseSpeed);
		AddActorWorldOffset(actorPos);

	}
}

// ダッシュ終了処理
void AMSGOCharacter::EndDash()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MaxFlySpeed = MaxWalkSpeed;
	GetCharacterMovement()->MaxAcceleration = MaxWalkAcceleration;
	GetCharacterMovement()->GravityScale = 1.0f;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	// 移動タイプを歩行に戻す
	MoveType = EMOVE_TYPE::Walk;

	StatusComponent->EndBoostDash();
}

// オーバーヒート時の処理
void AMSGOCharacter::OnOverHeat()
{
	EndDash();
}



// 視点操作
void AMSGOCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput((LookInput.Y * -1.0) * TurnRateGamepad * GetWorld()->GetDeltaSeconds());

}

// カメラの向いている方に向く
void AMSGOCharacter::RotToCamera(float InRotSpeed)
{
	// カメラの角度(Yawのみ)を取得
	FRotator cameraRot = FollowCamera->GetComponentRotation();
	cameraRot.Pitch = cameraRot.Roll = 0.0f;

	// 自身の角度(Yawのみ)を取得
	FRotator nowRot = GetActorRotation();
	nowRot.Pitch = nowRot.Roll = 0.0f;

	// カメラの向いている方向に回転
	SetActorRotation(FMath::RInterpTo(nowRot, cameraRot, GetWorld()->GetDeltaSeconds(), InRotSpeed));

}