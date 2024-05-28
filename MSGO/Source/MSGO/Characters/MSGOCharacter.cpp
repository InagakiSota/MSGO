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

//////////////////////////////////////////////////////////////////////////
// AMSGOCharacter

const float AMSGOCharacter::WALK_SPEED_MAX = 500.0f;
const float AMSGOCharacter::DASH_SPEED_MAX = 1000.0f;

AMSGOCharacter::AMSGOCharacter()
{
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

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED_MAX;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	bIsDash = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMSGOCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 移動
		enhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMSGOCharacter::Move);

		// 攻撃
		//enhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMSGOCharacter::);

		// 視点操作
		enhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMSGOCharacter::Look);

		// ダッシュ
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Started, this, &AMSGOCharacter::OnPressDash);
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AMSGOCharacter::OnReleaseDash);


		// ジャンプ
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMSGOCharacter::OnPressJump);
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AMSGOCharacter::OnReleaseJump);
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMSGOCharacter::UpdateJump);

	}
}

// 移動処理
void AMSGOCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if ((Controller != nullptr) && (MovementVector.Length() > 0.0f))
	{	
		MovementVector.Normalize();
		FVector2D inputDir = MovementVector.GetRotated(Controller->GetControlRotation().Yaw);


		AddMovementInput(FVector(inputDir.X, inputDir.Y, 0.0), 1.0);
	}
}

// ダッシュ　入力
void AMSGOCharacter::OnPressDash()
{
	GetCharacterMovement()->MaxWalkSpeed = DASH_SPEED_MAX;

	GetCharacterMovement()->GravityScale = 0.2;


	bIsDash = true;
}
// ダッシュ　リリース
void AMSGOCharacter::OnReleaseDash()
{
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED_MAX;

	GetCharacterMovement()->GravityScale = 1.0f;

	bIsDash = false;
}

// ジャンプ　入力
void AMSGOCharacter::OnPressJump()
{
	Jump();
}
// ジャンプ　リリース
void AMSGOCharacter::OnReleaseJump()
{
	StopJumping();

	GetCharacterMovement()->GravityScale = 1.0f;

}
// ジャンプ　入力中
void AMSGOCharacter::UpdateJump()
{
	FVector velocity = GetCharacterMovement()->Velocity;

	if (velocity.Z < 0)
	{
		GetCharacterMovement()->GravityScale = 0.2;
	}
}


// 視点操作
void AMSGOCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput((LookInput.Y * -1.0) * TurnRateGamepad * GetWorld()->GetDeltaSeconds());

}


