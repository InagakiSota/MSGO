// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/StaticDataManager.h"
#include "Characters/MSGOCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utility/MSGOBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameState/MSGOGameState.h"
#include "UI/MSGOUIManager.h"

UBoostCalculator::UBoostCalculator()
	: NowBoostState(EBOOST_STATE::None)
	, BoostDecrementValue(0)
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
	if (NowBoostState == EBOOST_STATE::BeginBoostIgnition)
	{
		//int32 BoostDecrement = 0;

		//if (OwnerCharacter->GetNowMoveType() == EMOVE_TYPE::Dash && (OwnerCharacter->GetNowJumpStatus() == EJUMP_STATUS::Rising || OwnerCharacter->GetNowJumpStatus() == EJUMP_STATUS::Hovering))
		//{
		//	BoostDecrement = StatusParam.BoostGaugeDecrement_BoostDash + StatusParam.BoostGaugeDecrement_Rising;
		//}
		//else if (OwnerCharacter->GetNowMoveType() == EMOVE_TYPE::Dash)
		//{
		//	BoostDecrement = StatusParam.BoostGaugeDecrement_BoostDash;
		//}
		//else if (OwnerCharacter->GetNowJumpStatus() == EJUMP_STATUS::Hovering || OwnerCharacter->GetNowJumpStatus() == EJUMP_STATUS::Rising)
		//{
		//	BoostDecrement = StatusParam.BoostGaugeDecrement_Rising;
		//}
		//UKismetSystemLibrary::PrintString(this, FString::FromInt(BoostDecrementValue));

		NowBoostCap -=(BoostDecrementValue * DeltaTime * 100.0f);

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
				BoostDecrementValue = 0.0f;
			}
		}
	}

	PrevBoostCap = NowBoostCap;

}

// ブースト消費開始
void UBoostCalculator::BeginBoost()
{
	NowBoostState = EBOOST_STATE::BeginBoostIgnition;
	
	if (OwnerCharacter->GetNowMoveType() == EMOVE_TYPE::Dash)
	{
		NowBoostCap -= StatusParam.BoostGaugeDecrement_BeginBoostDash;
	}
		
}
// ブースト消費終了
void UBoostCalculator::EndBoost()
{
	if (NowBoostState != EBOOST_STATE::OverHeat)
	{
		NowBoostState = EBOOST_STATE::None;
	}
}

// ブースト消費開始　ダッシュ
void UBoostCalculator::BeginBoost_Dash()
{
	NowBoostState = EBOOST_STATE::BeginBoostIgnition;
	
	NowBoostCap -= StatusParam.BoostGaugeDecrement_BeginBoostDash;

	BoostDecrementValue += StatusParam.BoostGaugeDecrement_BoostDash;
}
// ブースト終了処理　ダッシュ
void UBoostCalculator::EndBoost_Dash()
{
	if (NowBoostState != EBOOST_STATE::OverHeat && OwnerCharacter->GetNowJumpStatus() == EJUMP_STATUS::Idle)
	{
		NowBoostState = EBOOST_STATE::None;
	}
	BoostDecrementValue -= StatusParam.BoostGaugeDecrement_BoostDash;

}

// ブースト消費開始 ジャンプ
void UBoostCalculator::BeginBoost_Jump()
{
	NowBoostState = EBOOST_STATE::BeginBoostIgnition;

	BoostDecrementValue += StatusParam.BoostGaugeDecrement_Rising;
}
// ブースト消費終了　ジャンプ
void UBoostCalculator::EndBoost_Jump()
{
	if (NowBoostState != EBOOST_STATE::OverHeat && OwnerCharacter->GetNowMoveType() == EMOVE_TYPE::Walk)
	{
		NowBoostState = EBOOST_STATE::None;
	}
	BoostDecrementValue -= StatusParam.BoostGaugeDecrement_Rising;
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

	// UIまわりのセットアップ
	UMSGOUIManager* uiManager = GetUIManager();
	if (uiManager)
	{
		uiManager->SetNowBoost(NowBoostCap,GetIsOverHeat());
	}
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

	// UIまわりのセットアップ
	UMSGOUIManager* uiManager = GetUIManager();
	if (!uiManager)
	{
		return;
	}

	uiManager->SetupHPGauge(MaxHP);
	uiManager->SetupBoostGauge(MaxBoostCap);
}

// ブースト消費開始
void UCharacterStatusComponent::BeginBoost()
{
	BoostCalculator->BeginBoost();
}
// ブースト消費終了
void UCharacterStatusComponent::EndBoost()
{
	BoostCalculator->EndBoost();
}

// ブースト消費開始　ダッシュ
void UCharacterStatusComponent::BeginBoost_Dash()
{
	BoostCalculator->BeginBoost_Dash();
}
// ブースト終了処理　ダッシュ
void UCharacterStatusComponent::EndBoost_Dash()
{
	BoostCalculator->EndBoost_Dash();
}

// ブースト消費開始 ジャンプ
void UCharacterStatusComponent::BeginBoost_Jump()
{
	BoostCalculator->BeginBoost_Jump();
}
// ブースト消費終了　ジャンプ
void UCharacterStatusComponent::EndBoost_Jump()
{
	BoostCalculator->EndBoost_Jump();
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

// 被弾処理
void UCharacterStatusComponent::AddDamage(const FAttackCollisionPowerParameter& InAttackPowerParam)
{
	UKismetSystemLibrary::PrintString(this, FString::FromInt(InAttackPowerParam.BaseAttackPower));

	FCharacterStatusParameter statusParam = GetStatusParameter();

	float damage = (float)InAttackPowerParam.BaseAttackPower;
	
	// 攻撃の属性ごとにダメージのカット率を計算する
	switch (InAttackPowerParam.AttackType)
	{
	case EAttackType::Bullet:
		damage *= 1.0f - statusParam.DamageCutRate_Bullet;
		break;
	case EAttackType::Bomb:
		damage *= 1.0f - statusParam.DamageCutRate_Bomb;
		break;
	case EAttackType::Beam:
		damage *= 1.0f - statusParam.DamageCutRate_Beam;
		break;
	case EAttackType::Combat:
		damage *= 1.0f - statusParam.DamageCutRate_Combat;
		break;
	default:
		break;
	}

	NowHP -= damage;
	NowDownPoint -= InAttackPowerParam.DownPoint;

	// UIに反映
	UMSGOUIManager* uiManager = GetUIManager();
	if (!uiManager)
	{
		return;
	}

	uiManager->SetNowHP(NowHP);
}

// UIマネージャーの取得
UMSGOUIManager* UCharacterStatusComponent::GetUIManager()
{
	AMSGOGameState* gameState = Cast<AMSGOGameState>(UGameplayStatics::GetGameState(this));
	if (!gameState)
	{
		return nullptr;
	}
	UMSGOUIManager* uiManager = gameState->GetUIManager();

	return uiManager;
}