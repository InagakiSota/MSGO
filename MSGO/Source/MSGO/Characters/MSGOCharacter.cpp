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

	YawRotSpeed = 10.f;
	DashRiseSpeed = 1.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMSGOCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// �ړ�
		enhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMSGOCharacter::Move);
		enhancedInput->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMSGOCharacter::EndMove);

		// �U��
		//enhancedInput->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMSGOCharacter::);

		// ���_����
		enhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMSGOCharacter::Look);

		// �_�b�V��
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Started, this, &AMSGOCharacter::OnPressDash);
		enhancedInput->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AMSGOCharacter::OnReleaseDash);


		// �W�����v
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMSGOCharacter::OnPressJump);
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AMSGOCharacter::OnReleaseJump);
		enhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMSGOCharacter::UpdateJump);

	}
}

// �ړ�����
void AMSGOCharacter::Move(const FInputActionValue& Value)
{
	MoveInput = Value.Get<FVector2D>();

	if ((Controller != nullptr) && (MoveInput.Length() > 0.0f))
	{	
		RotToCamera(YawRotSpeed);

		MoveInput.Normalize();
		FVector2D inputDir = MoveInput.GetRotated(Controller->GetControlRotation().Yaw);

		AddMovementInput(FVector(inputDir.X, inputDir.Y, 0.0), 1.0);
	}
}

// �ړ��I��
void AMSGOCharacter::EndMove()
{
	MoveInput = FVector2D(0, 0);

	if (bIsDash)
	{
		OnReleaseDash();
	}

}

// �_�b�V���@����
void AMSGOCharacter::OnPressDash()
{
	if (MoveInput.Length() > 0.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = DASH_SPEED_MAX;
		GetCharacterMovement()->MaxFlySpeed = DASH_SPEED_MAX;
		GetCharacterMovement()->GravityScale = 0.1;

		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		bIsDash = true;
	}
	
}
// �_�b�V���@�����[�X
void AMSGOCharacter::OnReleaseDash()
{
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED_MAX;
	GetCharacterMovement()->MaxFlySpeed = WALK_SPEED_MAX;

	GetCharacterMovement()->GravityScale = 1.0f;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);


	bIsDash = false;
}

// �W�����v�@����
void AMSGOCharacter::OnPressJump()
{
	if (bIsDash)
	{
	}
	else
	{
		Jump();
	}
	
}
// �W�����v�@�����[�X
void AMSGOCharacter::OnReleaseJump()
{
	if (!bIsDash)
	{
		StopJumping();

		GetCharacterMovement()->GravityScale = 1.0f;
	}
	
}
// �W�����v�@���͒�
void AMSGOCharacter::UpdateJump()
{
	if (!bIsDash)
	{
		FVector velocity = GetCharacterMovement()->Velocity;

		if (velocity.Z < 0)
		{
			GetCharacterMovement()->GravityScale = 0.1;
		}
	
	}
	else
	{
		FVector actorPos = FVector(0.0,0.0,DashRiseSpeed);

		AddActorWorldOffset(actorPos);

	}
}


// ���_����
void AMSGOCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput((LookInput.Y * -1.0) * TurnRateGamepad * GetWorld()->GetDeltaSeconds());

}

// �J�����̌����Ă�����Ɍ���
void AMSGOCharacter::RotToCamera(float InRotSpeed)
{
	// �J�����̊p�x(Yaw�̂�)���擾
	FRotator cameraRot = FollowCamera->GetComponentRotation();
	cameraRot.Pitch = cameraRot.Roll = 0.0f;

	// ���g�̊p�x(Yaw�̂�)���擾
	FRotator nowRot = GetActorRotation();
	nowRot.Pitch = nowRot.Roll = 0.0f;

	// �J�����̌����Ă�������ɉ�]
	SetActorRotation(FMath::RInterpTo(nowRot, cameraRot, GetWorld()->GetDeltaSeconds(), InRotSpeed));

}