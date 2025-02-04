// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MSGOCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MSGO_API UMSGOCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TestNum = 0;


public:
	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetMyMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0);
	UFUNCTION(Server, Reliable)
	void Server_SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0);

	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetMaxWalkSpeed(const float& InMaxWalkSpeed = 0.f);
	UFUNCTION(Server, Reliable)
	void Server_SetMaxWalkSpeed(const float& InMaxWalkSpeed = 0.f);

	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetMaxAcceleration(const float& InMaxAcceleration = 0.f);
	UFUNCTION(Server, Reliable)
	void Server_SetMaxAcceleration(const float& InMaxAcceleration = 0.f);

	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetMaxFlySpeed(const float& InMaxFlySpeed = 0.f);
	UFUNCTION(Server, Reliable)
	void Server_SetMaxFlySpeed(const float& InMaxFlySpeed = 0.f);

	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetMaxFlySpeedPPT(const int32& InMaxFlySpeedPPT = 0);
	UFUNCTION(Server, Reliable)
	void Server_SetMaxFlySpeedPPT(const int32& InMaxFlySpeedPPT = 0);

	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetGravityScale(const float& InGravityScale = 0.f);
	UFUNCTION(Server, Reliable)
	void Server_SetGravityScale(const float& InGravityScale = 0.f);

	UFUNCTION(BlueprintCallable, Category = "MSGO|Movement")
	void SetVelocity(const FVector& InVelocity = FVector::ZeroVector);
	UFUNCTION(Server, Reliable)
	void Server_SetVelocity(const FVector& InVelocity = FVector::ZeroVector);


};
