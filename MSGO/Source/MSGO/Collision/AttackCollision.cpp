// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/AttackCollision.h"
#include "../Utility/MSGOBlueprintFunctionLibrary.h"
#include "../Characters/MSGOCharacter.h"

// Sets default values
AAttackCollision::AAttackCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("RootCollision")));

	// BoxComponent生成
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxCollision")));
	if (BoxCollision)
	{
		BoxCollision->SetupAttachment(RootComponent);
		BoxCollision->SetBoxExtent(FVector(0.f));
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxCollision->SetComponentTickEnabled(false);
	}

#if WITH_EDITOR

	// テスト用にStaticMesh生成
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("StaticMesh")));
	
	UStaticMesh* mesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Cube.Cube"));
	StaticMesh->SetStaticMesh(mesh);

	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh->SetVisibility(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
#endif

	PrimaryActorTick.bCanEverTick = true;

	bIsUsing = false;
	MoveTotalSeconds = 0.0f;

	this->SleepObject();
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
	if (MoveTotalSeconds >= UMSGOBlueprintFunctionLibrary::FrameToSeconds(AttackParam.CollisionParam.LiveMaxFrame))
	{
		SleepObject();
	}

	// 指定した方向に移動
	AddActorLocalOffset(AttackParam.MovementParam.MoveDir * AttackParam.MovementParam.MoveSpeed * DeltaTime * 100.0f);
	// タイマー加算
	MoveTotalSeconds += DeltaTime;
}

bool AAttackCollision::WakeObject(const FAttackParameter& InAttackParam, const FMachineTeamID& InOwnerTeamID)
{
	if (BoxCollision == nullptr)
	{
		return false;
	}

	// 攻撃パラメータ取得
	AttackParam = InAttackParam;


	// 移動パラメータから初期座標、初期角度をセット
	SetActorLocation(AttackParam.MovementParam.StartPos);
	SetActorRotation(AttackParam.MovementParam.StartRot);

	AttackParam.MovementParam.MoveDir.Normalize();

#if WITH_EDITOR
	// テスト描画
	BoxCollision->bHiddenInGame = false;
	BoxCollision->SetVisibility(true);

	StaticMesh->SetVisibility(true);

#endif
	//OwnerCharacterPtr = InOwner;

	OwnerTeamID = InOwnerTeamID;

	SetActorTickEnabled(true);

	MoveTotalSeconds = 0.0f;

	bIsUsing = true;

	// コリジョンパラメータからサイズのセットアップ
	BoxCollision->SetBoxExtent(AttackParam.CollisionParam.CollisionSize);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetComponentTickEnabled(true);


	return true;
}

bool AAttackCollision::SleepObject()
{
	// コリジョンの無効化
	BoxCollision->SetBoxExtent(FVector(0.f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetComponentTickEnabled(false);

#if WITH_EDITOR
	// テスト描画 非表示に
	BoxCollision->bHiddenInGame = true;
	BoxCollision->SetVisibility(false);

	StaticMesh->SetVisibility(false);

#endif
	// Tickを止める
	this->SetActorTickEnabled(false);

	// 未使用にする
	bIsUsing = false;

	// タイマーリセット
	MoveTotalSeconds = 0.0f;

	return true;
}