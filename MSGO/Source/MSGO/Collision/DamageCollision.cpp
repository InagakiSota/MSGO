// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/DamageCollision.h"

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

	// ...
	
}


// Called every frame
void UDamageCollision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// コリジョンのセットアップ
bool UDamageCollision::SetupCollision(const FDamageCollisionParametr& InDamageCollParam)
{
	//if (!BoxCollision)
	//{
	//	return false;
	//}

	this->SetBoxExtent(InDamageCollParam.CollisionSize);

	return true;
}
