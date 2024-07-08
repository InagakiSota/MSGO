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
	BoxCollision->SetBoxExtent(InAttackCollArg.CollisionSize);

	SetActorLocation(InStartPos);

	PrimaryActorTick.bCanEverTick = true;

	return true;
}
