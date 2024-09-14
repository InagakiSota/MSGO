// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MSGOGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MSGO_API UMSGOGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	void AddGameplayTags(const FGameplayTagContainer GameplayTags);

	UFUNCTION(BlueprintCallable, Category = "GamePlayAbility")
	void RemoveGameplayTags(const FGameplayTagContainer GameplayTags);
	
};
