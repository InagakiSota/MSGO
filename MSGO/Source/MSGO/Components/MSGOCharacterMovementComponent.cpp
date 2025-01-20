// Fill out your copyright notice in the Description page of Project Settings.


#include "MSGOCharacterMovementComponent.h"
#include "CharacterMovementComponentAsync.h"

void UMSGOCharacterMovementComponent::Server_SetMovementMode_Implementation(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
    SetMovementMode(NewMovementMode, NewCustomMode);
}

void UMSGOCharacterMovementComponent::Server_SetMaxWalkSpeed_Implementation(const float& InMaxWalkSpeed)
{
    this->MaxWalkSpeed = InMaxWalkSpeed;
}

void UMSGOCharacterMovementComponent::Server_SetMaxAcceleration_Implementation(const float& InMaxAcceleration)
{
    this->MaxAcceleration = InMaxAcceleration;

}

void UMSGOCharacterMovementComponent::Server_SetMaxFlySpeed_Implementation(const float& InMaxFlySpeed)
{
    this->MaxFlySpeed = InMaxFlySpeed;

}

void UMSGOCharacterMovementComponent::Server_SetGravityScale_Implementation(const float& InGravityScale)
{
    this->GravityScale = InGravityScale;

}
