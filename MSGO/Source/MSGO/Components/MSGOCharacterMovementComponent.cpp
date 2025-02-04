// Fill out your copyright notice in the Description page of Project Settings.


#include "MSGOCharacterMovementComponent.h"
#include "CharacterMovementComponentAsync.h"
#include "Kismet/KismetSystemLibrary.h"

void UMSGOCharacterMovementComponent::SetMyMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
    Super::SetMovementMode(NewMovementMode, NewCustomMode);
    Server_SetMovementMode(NewMovementMode, NewCustomMode);
}
void UMSGOCharacterMovementComponent::Server_SetMovementMode_Implementation(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
    SetMovementMode(NewMovementMode, NewCustomMode);
}

void UMSGOCharacterMovementComponent::SetMaxWalkSpeed(const float& InMaxWalkSpeed)
{
    MaxWalkSpeed = InMaxWalkSpeed;
    if (GetOwnerRole() != ENetRole::ROLE_Authority)
    {
        Server_SetMaxWalkSpeed(InMaxWalkSpeed);
    }
}
void UMSGOCharacterMovementComponent::Server_SetMaxWalkSpeed_Implementation(const float& InMaxWalkSpeed)
{
    this->MaxWalkSpeed = InMaxWalkSpeed;
}

void UMSGOCharacterMovementComponent::SetMaxAcceleration(const float& InMaxAcceleration)
{
    MaxAcceleration = InMaxAcceleration;

    if (GetOwnerRole() != ENetRole::ROLE_Authority)
    {
        Server_SetMaxAcceleration(InMaxAcceleration);
    }
}
void UMSGOCharacterMovementComponent::Server_SetMaxAcceleration_Implementation(const float& InMaxAcceleration)
{
    this->MaxAcceleration = InMaxAcceleration;
}

void UMSGOCharacterMovementComponent::SetMaxFlySpeed(const float& InMaxFlySpeed)
{
    MaxFlySpeed = InMaxFlySpeed;

    if (GetOwnerRole() != ENetRole::ROLE_Authority)
    {
        Server_SetMaxFlySpeed(InMaxFlySpeed);
    }
}
void UMSGOCharacterMovementComponent::Server_SetMaxFlySpeed_Implementation(const float& InMaxFlySpeed)
{
    this->MaxFlySpeed = InMaxFlySpeed;
}

void UMSGOCharacterMovementComponent::SetMaxFlySpeedPPT(const int32& InMaxFlySpeedPPT)
{
    float maxFlySpeedFloat = InMaxFlySpeedPPT * 0.001f;
    MaxFlySpeed = maxFlySpeedFloat;
    if (GetOwnerRole() != ENetRole::ROLE_Authority)
    {
        Server_SetMaxFlySpeed(maxFlySpeedFloat);
    }
}
void UMSGOCharacterMovementComponent::Server_SetMaxFlySpeedPPT_Implementation(const int32& InMaxFlySpeedPPT)
{
    this->MaxFlySpeed = InMaxFlySpeedPPT * 0.001;
}

void UMSGOCharacterMovementComponent::SetGravityScale(const float& InGravityScale)
{
    GravityScale = InGravityScale;
    if (GetOwnerRole() != ENetRole::ROLE_Authority)
    {
        Server_SetGravityScale(InGravityScale);
    }
}
void UMSGOCharacterMovementComponent::Server_SetGravityScale_Implementation(const float& InGravityScale)
{
    this->GravityScale = InGravityScale;

}

void UMSGOCharacterMovementComponent::SetVelocity(const FVector& InVelocity)
{
    Velocity = InVelocity;
    if (GetOwnerRole() != ENetRole::ROLE_Authority)
    {
        Server_SetVelocity(InVelocity);
    }
}
void UMSGOCharacterMovementComponent::Server_SetVelocity_Implementation(const FVector& InVelocity)
{
    this->Velocity = InVelocity;

}
