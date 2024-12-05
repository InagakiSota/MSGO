// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MSGOGameplayAbility.h"
#include "AbilitySystemComponent.h"

void UMSGOGameplayAbility::AddGameplayTags(const FGameplayTagContainer GameplayTags)
{
    UAbilitySystemComponent* cmp = GetAbilitySystemComponentFromActorInfo();

    cmp->AddLooseGameplayTags(GameplayTags);
}

void UMSGOGameplayAbility::RemoveGameplayTags(const FGameplayTagContainer GameplayTags)
{
    UAbilitySystemComponent* cmp = GetAbilitySystemComponentFromActorInfo();

    cmp->RemoveLooseGameplayTags(GameplayTags);
}
