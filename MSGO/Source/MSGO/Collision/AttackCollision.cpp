// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/AttackCollision.h"
#include "../Utility/MSGOBlueprintFunctionLibrary.h"
#include "../Characters/MSGOCharacter.h"

// Sets default values
AAttackCollision::AAttackCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("RootCollision")));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxCollision")));
	if (BoxCollision)
	{
		BoxCollision->SetupAttachment(RootComponent);
		BoxCollision->SetBoxExtent(FVector(0.f));
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxCollision->SetComponentTickEnabled(false);
	}

	PrimaryActorTick.bCanEverTick = true;

	bIsUsing = false;
	MoveTotalSeconds = 0.0f;
}

// Called when the game starts or when spawned
void AAttackCollision::BeginPlay()
{
	Super::BeginPlay();
	
	this->SetActorTickEnabled(false);
}

// Called every frame
void AAttackCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// コリジョンの生存時間を越えたら削除
	if (MoveTotalSeconds >= UMSGOBlueprintFunctionLibrary::FrameToSeconds(AttackCollParam.LiveMaxFrame))
	{
		SleepObject();
	}

	// 指定した方向に移動
	AddActorLocalOffset(MovementParam.MoveDir * MovementParam.MoveSpeed * DeltaTime * 100.0f);

	MoveTotalSeconds += DeltaTime;
}

bool AAttackCollision::WakeObject(const FAttackCollisionParameter& InAttackCollArg, const FAttackCollisionMovementParameter& InMovementArg, AMSGOCharacter* InOwner)
{
	if (BoxCollision == nullptr)
	{
		return false;
	}

	// 既に起動中の場合は処理しない
	//if (bIsUsing)
	//{
	//	return false;
	//}

	// 攻撃コリジョンのパラメータ取得
	AttackCollParam = InAttackCollArg;


	BoxCollision->SetBoxExtent(InAttackCollArg.CollisionSize);

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BoxCollision->SetComponentTickEnabled(true);

	// コリジョンの移動パラメータ取得
	MovementParam = InMovementArg;

	SetActorLocation(InMovementArg.StartPos);
	SetActorRotation(InMovementArg.StartRot);

	MovementParam.MoveDir.Normalize();

	// テスト描画(削除予定)
	BoxCollision->bHiddenInGame = false;
	BoxCollision->SetVisibility(true);

	OwnerCharacterPtr = InOwner;

	SetActorTickEnabled(true);

	bIsUsing = true;

	return true;
}

bool AAttackCollision::SleepObject()
{

	BoxCollision->SetBoxExtent(FVector(0.f));

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollision->SetComponentTickEnabled(false);

	// テスト描画(削除予定)
	BoxCollision->bHiddenInGame = true;
	BoxCollision->SetVisibility(false);


	this->SetActorTickEnabled(false);

	bIsUsing = false;

	MoveTotalSeconds = 0.0f;

	return true;
}