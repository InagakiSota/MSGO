// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/StaticDataManager.h"
#include "Characters/MSGOCharacter.h"

// Sets default values for this component's properties
UCharacterStatusComponent::UCharacterStatusComponent()
	: NowHP(0)
	, MaxHP(0)
	, NowBoostCap(0)
	, MaxBoostCap(0)
	, NowDownPoint(0)
	, MaxDownPoint(0)
	, OwnerCharacter(nullptr)
	, bIsCurrentDash(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// 所有者を取得
	OwnerCharacter = Cast<AMSGOCharacter>(GetOwner());

}


// Called every frame
void UCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCurrentDash)
	{
		NowBoostCap--;
	}

	UKismetSystemLibrary::PrintString(this, FString::FromInt(NowBoostCap), true, true, FLinearColor::Red, 0.0166);
	// ...
}

// パラメータのセットアップ
// @param			InMachineID		機体ID
void UCharacterStatusComponent::SetupParameter(int32 InMachineID)
{
	UStaticDataManager::GetCharacterParameterData(this, InMachineID, StatusParameter);

	NowHP = MaxHP = StatusParameter.MaxHP;
	NowBoostCap = MaxBoostCap = StatusParameter.MaxBoostCap;
	NowDownPoint = MaxDownPoint = StatusParameter.MaxDownPoint;

}

// ブーストダッシュの開始
void UCharacterStatusComponent::BeginBoostDash()
{
	bIsCurrentDash = true;
}
// ブーストダッシュ終了
void UCharacterStatusComponent::EndBoostDash()
{
	bIsCurrentDash = false;
}
