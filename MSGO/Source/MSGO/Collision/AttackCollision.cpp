// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/AttackCollision.h"

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

	PrimaryActorTick.bCanEverTick = false;


	bIsUsing = false;

}

// Called when the game starts or when spawned
void AAttackCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAttackCollision::WakeObject(const FAttackCollisionStr& InAttackCollArg, const FVector& InStartPos)
{
	if (BoxCollision == nullptr)
	{
		return false;
	}

	BoxCollision->SetBoxExtent(InAttackCollArg.CollisionSize);

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BoxCollision->SetComponentTickEnabled(true);

	SetActorLocation(InStartPos);

	PrimaryActorTick.bCanEverTick = true;

	// テスト描画(削除予定)
	BoxCollision->bHiddenInGame = false;
	BoxCollision->SetVisibility(true);

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


	PrimaryActorTick.bCanEverTick = false;

	return true;
}