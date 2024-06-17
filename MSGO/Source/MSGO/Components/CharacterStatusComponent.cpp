// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/StaticDataManager.h"
#include "Characters/MSGOCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utility/MSGOBlueprintFunctionLibrary.h"

UBoostCalculator::UBoostCalculator()
	: NowBoostState(EBOOST_STATE::None)
{

}

TStatId UBoostCalculator::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMyGameInstanceSubsystem, STATGROUP_Tickables);
}

void UBoostCalculator::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Log, TEXT("DeltaTime=%f"), DeltaTime);

	// ブースト容量の計算
	CalcNowBoostCap(DeltaTime);
}

// 現在のブースト容量の計算
void UBoostCalculator::CalcNowBoostCap(float DeltaTime)
{
	// ブーストダッシュ中はゲージを減らす
	if (NowBoostState == EBOOST_STATE::BeginBoostDash)
	{
		NowBoostCap -=( StatusParam.BoostGaugeDecrement_BoostDash * DeltaTime * 100.0f);

		// ブーストゲージが0になったらオーバーヒートフラグを立てる
		if (NowBoostCap <= 0 && NowBoostState != EBOOST_STATE::OverHeat)
		{
			NowBoostState = EBOOST_STATE::OverHeat;
		}
	}

	// ブースト消費がされておらずキャラクターが接地していればブースト回復
	if (PrevBoostCap == NowBoostCap && NowBoostCap != StatusParam.MaxBoostCap && !OwnerCharacter->GetCharacterMovement()->IsFalling())
	{
		// オーバーヒート中は一定時間経過するまで回復しない
		if (NowBoostState == EBOOST_STATE::OverHeat)
		{
			BeginChargeTimerWithOverHeat += DeltaTime;

			if (BeginChargeTimerWithOverHeat < UMSGOBlueprintFunctionLibrary::FrameToSeconds(StatusParam.BeginBoostChargeFrame))
			{
				return;
			}
		}

		// ブーストゲージを回復させる
		int32 boostGainValue = NowBoostState != EBOOST_STATE::OverHeat ? StatusParam.BoostGaugeIncrement_Normal : StatusParam.BoostGaugeIncrement_OverHeat;
		NowBoostCap += boostGainValue * DeltaTime * 100.0f;

		if (NowBoostCap >= StatusParam.MaxBoostCap)
		{
			NowBoostCap = StatusParam.MaxBoostCap;
			// オーバーヒートフラグが立っていたら下げる
			if (NowBoostState == EBOOST_STATE::OverHeat)
			{
				NowBoostState = EBOOST_STATE::None;
				BeginChargeTimerWithOverHeat = 0.0f;
			}
		}
	}

	PrevBoostCap = NowBoostCap;

}

// ブーストダッシュ開始
void UBoostCalculator::BeginBoostDash()
{
	NowBoostState = EBOOST_STATE::BeginBoostDash;
	NowBoostCap -= StatusParam.BoostGaugeDecrement_BeginBoostDash;

}
// ブーストダッシュ終了
void UBoostCalculator::EndBoostDash()
{
	if (NowBoostState != EBOOST_STATE::OverHeat)
	{
		NowBoostState = EBOOST_STATE::None;
	}
}

// ステータスパラメータのセットアップ
void UBoostCalculator::SetupStatusParam(const FCharacterStatusParameter& InStatusParam)
{
	StatusParam = InStatusParam;
	NowBoostCap = StatusParam.MaxBoostCap;
}


// Sets default values for this component's properties
UCharacterStatusComponent::UCharacterStatusComponent()
	: NowHP(0)
	, MaxHP(0)
	, NowBoostCap(0)
	, MaxBoostCap(0)
	, NowDownPoint(0)
	, MaxDownPoint(0)
	, OwnerCharacter(nullptr)
	, bIsBroadcastDelegate(false)
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
	check(OwnerCharacter);

	BoostCalculator = NewObject<UBoostCalculator>();
	check(BoostCalculator);

	BoostCalculator->SetOwnerCharacter(OwnerCharacter);

}

void UCharacterStatusComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnOverHeatDelegate.RemoveAll(this);
}



// Called every frame
void UCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ブースト計算クラスからブースト容量を取得
	NowBoostCap = BoostCalculator->GetNowBoostCap();

	// ブースト容量が0になったらデリゲートを実行
	if (NowBoostCap <= 0 && PrevBoostCap != NowBoostCap)
	{
		// 登録されていればデリゲートを実行
		if (OnOverHeatDelegate.IsBound())
		{
			OnOverHeatDelegate.Broadcast();
			//bIsBroadcastDelegate = true;
		}
	}

	PrevBoostCap = NowBoostCap;
}

// パラメータのセットアップ
// @param			InMachineID		機体ID
void UCharacterStatusComponent::SetupParameter(int32 InMachineID)
{
	UStaticDataManager::GetCharacterParameterData(this, InMachineID, StatusParameter);

	BoostCalculator->SetupStatusParam(StatusParameter);

	NowHP = MaxHP = StatusParameter.MaxHP;
	NowDownPoint = MaxDownPoint = StatusParameter.MaxDownPoint;
	NowBoostCap = MaxBoostCap = BoostCalculator->GetNowBoostCap();

}

// ブーストダッシュの開始
void UCharacterStatusComponent::BeginBoostDash()
{
	BoostCalculator->BeginBoostDash();
}
// ブーストダッシュ終了
void UCharacterStatusComponent::EndBoostDash()
{
	BoostCalculator->EndBoostDash();
}

bool UCharacterStatusComponent::GetIsOverHeat()
{
	return BoostCalculator->GetIsOverHeat();
}


// 現在のスピードを取得
const int32 UCharacterStatusComponent::GetNowSpeed()
{
	if (BoostCalculator)
	{
		return BoostCalculator->GetNowBoostSpeed();
	}

	return 0;
}