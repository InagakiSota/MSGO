// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/DamageCollision.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AttackCollision.h"
#include "../Characters/MSGOCharacter.h"

// Sets default values for this component's properties
UDamageCollision::UDamageCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxCollision")));
	//if (BoxCollision)
	//{
	//	BoxCollision->SetBoxExtent(FVector(0.f));
	//	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//	BoxCollision->SetComponentTickEnabled(false);
	//}

	// ...
}


// Called when the game starts
void UDamageCollision::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddUniqueDynamic(this, &UDamageCollision::OnBeginOverlap);
	// ...
	
}

void UDamageCollision::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnComponentBeginOverlap.RemoveDynamic(this, &UDamageCollision::OnBeginOverlap);
}


// Called every frame
void UDamageCollision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// コリジョンのセットアップ
bool UDamageCollision::SetupCollision(const FDamageCollisionParameter& InDamageCollParam)
{
	this->SetBoxExtent(InDamageCollParam.CollisionSize);

	return true;
}

// オーバーラップ開始処理(被弾処理)
void UDamageCollision::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UKismetSystemLibrary::PrintString(this, "BeginOverlap");

	// 攻撃コリジョンがヒットしたかをチェック
	if (AAttackCollision* attackColl = Cast<AAttackCollision>(Other))
	{
		// 自身の使用者を取得
		AMSGOCharacter* ownerChara = Cast<AMSGOCharacter>(GetOwner());
		if (!ownerChara)
		{
			return;
		}

		//// 攻撃コリジョンの使用者を取得
		//AMSGOCharacter* attackOwner = attackColl->GetOwnerCharacter();
		////　攻撃の使用者がNull、もしくは自身の使用者と同じ場合は処理しない
		//if (!attackOwner || ownerChara == attackOwner)
		//{
		//	return;
		//}

		if (!ownerChara->HasAuthority())
		{
			return;
		}

		// 使用者と被弾者のIDが同じ場合は処理しない
		if (attackColl->GetOwnerTeamID() == ownerChara->MachineTeamID)
		{
			return;
		}

		//if(owner)

		// 攻撃コリジョンを削除（いったん）
		attackColl->SleepObject();

		// 攻撃者とチームIDが異なる場合はダメージ処理
		if (attackColl->GetOwnerTeamID().TeamID != ownerChara->MachineTeamID.TeamID)
		{
			// ここにダメージ処理を書く
			ownerChara->AddDamage(attackColl->GetAttackPowerParameter());
		}
	}
}
