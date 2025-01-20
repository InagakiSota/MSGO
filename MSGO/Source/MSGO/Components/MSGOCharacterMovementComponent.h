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
	// SetMovementModeをサーバーで呼ぶ用
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "MSGO|Component", meta = (DisplayName = "SetMovementMode"))
	void Server_SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0);

	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetMaxWalkSpeed(const float& InMaxWalkSpeed = 0.f);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetMaxAcceleration(const float& InMaxAcceleration = 0.f);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetMaxFlySpeed(const float& InMaxFlySpeed = 0.f);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetGravityScale(const float& InGravityScale = 0.f);

};
