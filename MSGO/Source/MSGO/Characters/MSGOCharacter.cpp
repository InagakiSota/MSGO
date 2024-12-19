// Copyright Epic Games, Inc. All Rights Reserved.

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
#include "Kismet/KismetMathLibrary.h"
#include "Components/CharacterStatusComponent.h"
#include "Structs/ParameterStructs.h"
#include "Utility/MSGOBlueprintFunctionLibrary.h"
#include "Collision/AttackCollision.h"
#include "Collision/DamageCollision.h"
#include "../GameState/MSGOGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/NetDriver.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// AMSGOCharacter


AMSGOCharacter::AMSGOCharacter()
{
	// ステータスコンポーネントをアタッチ
	StatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("CharacterStatusComponent"));

	// ダメージコリジョンをアタッチ
	DamageCollision = CreateDefaultSubobject<UDamageCollision>(TEXT("DamageCollision"));
	//AddOwnedComponent(DamageCollision);
	DamageCollision->SetupAttachment(GetRootComponent());

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
	GetCharacterMovement()->SetIsReplicated(true);

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

	BoostMoveTimer = 0.0f;
	TargetSeconds = 0.0f;
	BeginRiseHeight = 0.0;

	NowBoostSpeedStatus = EBOOST_SPEED_STATUS::InitSpeed;
	NowJumpStatus = EJUMP_STATUS::Idle;

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
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
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	AttackCollision = GetWorld()->SpawnActor<AAttackCollision>(AAttackCollision::StaticClass());
	if (AttackCollision)
	{
		AttackCollision->SleepObject();
	}

	MyRotate = GetActorRotation();
	//APlayerCameraManager* cameraManager = UGameplayStati

}

void AMSGOCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		BeginRiseHeight = 0.f;
		NowJumpStatus = EJUMP_STATUS::Idle;
	}

	//if (AttackCollision && AttackCollision->GetIsUsing())
	//{
	//	AttackCollision->Tick(DeltaSeconds);
	//}

	//UGameplayStatics::GetGame
}

void AMSGOCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// レプリケートする変数を追加
	DOREPLIFETIME(AMSGOCharacter, MyRotate);

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

	// 初速を代入
	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetStatusParameter().InitSpeed;
	GetCharacterMovement()->MaxFlySpeed = StatusComponent->GetStatusParameter().InitSpeed;
	GetCharacterMovement()->MaxAcceleration = StatusComponent->GetStatusParameter().MaxAcceleration;
	GetCharacterMovement()->GravityScale = 0.0;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	// 移動タイプをダッシュにする
	MoveType = EMOVE_TYPE::Dash;

	AddActorWorldOffset(FVector(0.0, 0.0, 10.0f));

	StatusComponent->BeginBoost_Dash();

	// 最高速度に移行するまでの秒数を算出
	TargetSeconds = UMSGOBlueprintFunctionLibrary::FrameToSeconds(StatusComponent->GetStatusParameter().TransitionFrame_MaxSpeed);


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
	
	// ニュートラル時の移動処理
	if (MoveInput.Length() <= 0.0f)
	{
		InputMove(FVector2D(1.0f, 0.0f));
	}

	BoostMoveTimer += this->GetWorld()->DeltaTimeSeconds;
	float targetSeconds = 0.0f;
	float targetSecondsRate = BoostMoveTimer / TargetSeconds;
	float moveSpeed = 0.0f;

	switch (NowBoostSpeedStatus)
	{
	// 初速
	case EBOOST_SPEED_STATUS::InitSpeed:
		moveSpeed = UKismetMathLibrary::Ease(StatusComponent->GetStatusParameter().InitSpeed, StatusComponent->GetStatusParameter().MaxSpeed, targetSecondsRate, EEasingFunc::EaseIn);
		
		if (targetSecondsRate >= 1.0f)
		{
			BoostMoveTimer = 0.0f;
			// 最高速度維持フレームを算出
			TargetSeconds = UMSGOBlueprintFunctionLibrary::FrameToSeconds(StatusComponent->GetStatusParameter().SustainedFrame_MaxSpeed);

			NowBoostSpeedStatus = EBOOST_SPEED_STATUS::MaxSpeed;
		}
		break;
	// 最高速度
	case EBOOST_SPEED_STATUS::MaxSpeed:
		moveSpeed = StatusComponent->GetStatusParameter().MaxSpeed;

		if (targetSecondsRate >= 1.0f)
		{
			BoostMoveTimer = 0.0f;
			// 巡航速度移行フレームを算出
			TargetSeconds = UMSGOBlueprintFunctionLibrary::FrameToSeconds(StatusComponent->GetStatusParameter().TransitionFrame_CrusingSpeed);

			NowBoostSpeedStatus = EBOOST_SPEED_STATUS::CrusingSpeed;

		}

		break;
	case EBOOST_SPEED_STATUS::CrusingSpeed:
		// 巡航速度に移行したらそのまま維持
		if (targetSecondsRate >= 1.0f)
		{
			targetSecondsRate = 1.0f;
		}

		moveSpeed = UKismetMathLibrary::Ease(StatusComponent->GetStatusParameter().MaxSpeed, StatusComponent->GetStatusParameter().CrusingSpeed, targetSecondsRate, EEasingFunc::EaseOut);

		break;
	default:
		break;

	}

	//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(moveSpeed));
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxFlySpeed = moveSpeed;
}

// ダッシュ終了処理
void AMSGOCharacter::EndDash()
{
	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetStatusParameter().MaxWalkSpeed;
	GetCharacterMovement()->MaxFlySpeed = StatusComponent->GetStatusParameter().MaxWalkSpeed;
	GetCharacterMovement()->MaxAcceleration = StatusComponent->GetStatusParameter().MaxAcceleration;
	GetCharacterMovement()->GravityScale = 1.0f;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	// 移動タイプを歩行に戻す
	MoveType = EMOVE_TYPE::Walk;

	if (NowJumpStatus == EJUMP_STATUS::Rising || NowJumpStatus == EJUMP_STATUS::Hovering)
	{
		NowJumpStatus = EJUMP_STATUS::Falling;
	}

	//if (NowJumpStatus == EJUMP_STATUS::Idle)
	{
		StatusComponent->EndBoost_Dash();
	}
		

	BoostMoveTimer = 0.f;
	NowBoostSpeedStatus = EBOOST_SPEED_STATUS::InitSpeed;
}


// ジャンプ　入力
void AMSGOCharacter::OnPressJump()
{
	// オバヒ中ならただのジャンプ
	if (MoveType == EMOVE_TYPE::Walk && StatusComponent->GetIsOverHeat())
	{
		Jump();
		return;
	}

	switch (NowJumpStatus)
	{
	// アイドル
	case EJUMP_STATUS::Idle:
		// ジャンプ開始時の高さを種痘
		BeginRiseHeight = GetActorLocation().Z;
		// ジャンプのステートを上昇に変える
		NowJumpStatus = EJUMP_STATUS::Rising;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		break;
	case EJUMP_STATUS::Falling:
		NowJumpStatus = EJUMP_STATUS::Hovering;
		GetCharacterMovement()->Velocity.Z = 0.0f;

		break;
	default:
		break;
	}
	
	StatusComponent->BeginBoost_Jump();

}
// ジャンプ　リリース
void AMSGOCharacter::OnReleaseJump()
{
	if (MoveType == EMOVE_TYPE::Dash)
	{
		//NowJumpStatus = EJUMP_STATUS::Falling;
		StatusComponent->EndBoost_Jump();
		return;
	}

	EndJump();
}
// ジャンプ　入力中
void AMSGOCharacter::UpdateJump()
{
	// オバヒ中なら処理しない
	if (StatusComponent->GetIsOverHeat())
	{
		return;
	}

	switch (NowJumpStatus)
	{
	// 上昇
	case EJUMP_STATUS::Rising:
		// 高度上限に達したらホバリングに移行
		if (IsHeightLimit())
		{
			NowJumpStatus = EJUMP_STATUS::Hovering;
		}
		// 高度上限でなければ上昇
		else
		{
			FVector riseOffset = FVector(0, 0, StatusComponent->GetStatusParameter().JumpRiseSpeed) * 100.0f * GetWorld()->GetDeltaSeconds();
			AddActorWorldOffset(riseOffset);
		}

		break;
	// ホバリング
	case EJUMP_STATUS::Hovering:
		if (MoveType == EMOVE_TYPE::Walk)
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			GetCharacterMovement()->GravityScale = 0.1f;
		}
		break;
	// 落下中
	case EJUMP_STATUS::Falling:
		NowJumpStatus = EJUMP_STATUS::Hovering;

		break;
	default:
		break;
	}
}

// ジャンプ終了処理
void AMSGOCharacter::EndJump()
{
	if (NowJumpStatus == EJUMP_STATUS::Rising || NowJumpStatus == EJUMP_STATUS::Hovering)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		GetCharacterMovement()->GravityScale = 1.0f;

		NowJumpStatus = EJUMP_STATUS::Falling;

	}

	if (MoveType == EMOVE_TYPE::Walk)
	{
		StatusComponent->EndBoost_Jump();
	}
}

// オーバーヒート時の処理
void AMSGOCharacter::OnOverHeat()
{
	EndDash();
	EndJump();
}



// 視点操作
void AMSGOCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput((LookInput.Y * -1.0) * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}


// カメラの向いている方に向く
//void AMSGOCharacter::RotToCamera(float InRotSpeed)
//{
//	// カメラの角度(Yawのみ)を取得
//	FRotator cameraRot = FollowCamera->GetComponentRotation();
//	cameraRot.Pitch = cameraRot.Roll = 0.0f;
//
//	// 自身の角度(Yawのみ)を取得
//	FRotator nowRot = GetActorRotation();
//	nowRot.Pitch = nowRot.Roll = 0.0f;
//
//	// カメラの向いている方向に回転
//	MyRotate = FMath::RInterpTo(nowRot, cameraRot, GetWorld()->GetDeltaSeconds(), InRotSpeed);
//	
//	SetActorRotation(MyRotate);
//}

// カメラの向いている方に向く
void AMSGOCharacter::RotToCamera_Implementation(float InRotSpeed)
{
	// カメラの角度(Yawのみ)を取得
	FRotator cameraRot = FollowCamera->GetComponentRotation();
	cameraRot.Pitch = cameraRot.Roll = 0.0f;

	// 自身の角度(Yawのみ)を取得
	FRotator nowRot = GetActorRotation();
	nowRot.Pitch = nowRot.Roll = 0.0f;

	// カメラの向いている方向に回転
	MyRotate = FMath::RInterpTo(nowRot, cameraRot, GetWorld()->GetDeltaSeconds(), InRotSpeed);
	
	SetActorRotation(MyRotate);
}
bool AMSGOCharacter::RotToCamera_Validate(float InRotSpeed)
{
	return true;
}


// 高度上限かのチェック
// return		trueなら高度上限
bool AMSGOCharacter::IsHeightLimit()
{
	return GetActorLocation().Z - BeginRiseHeight >= StatusComponent->GetStatusParameter().JumpRiseHeight;
}

// 被弾処理
void AMSGOCharacter::AddDamage(const FAttackCollisionPowerParameter& InAttackPowerParam)
{
	StatusComponent->AddDamage(InAttackPowerParam);
}

// キャラの向きの変数が更新された際に呼ばれる
void AMSGOCharacter::OnRep_MyRotate()
{
	SetActorRotation(MyRotate);

	//UKismetSystemLibrary::PrintString(this, HasAuthority() ? TEXT("true") : TEXT("false"));
}
