// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/MSGOGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MSGOUIManager.h"
#include "Characters/MSGOCharacter.h"
#include "Collision/AttackCollisionPool.h"

void AMSGOGameState::BeginPlay()
{
    Super::BeginPlay();

    UIManager = NewObject<UMSGOUIManager>();

    //UIManager->SetupHPGauge(100);

    if (!UIManager)
    {
        return;
    }

    if (AMSGOCharacter* msgoChara = Cast<AMSGOCharacter>(UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0)))
    {
        UIManager->SetupOnBeginPlay(msgoChara);
    }

    AttackCollisionPool = NewObject<UAttackCollisionPool>();
    if (AttackCollisionPool)
    {
        AttackCollisionPool->BeginPlay();
    }
}

void AMSGOGameState::BeginDestroy()
{
    Super::BeginDestroy();

    if (AttackCollisionPool)
    {
        //AttackCollisionPool->BeginDestroy();
    }
}

AMSGOGameState* AMSGOGameState::Get(const UObject* WorldContextObject)
{
    UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    return World ? Cast<AMSGOGameState>(World->GetGameState()) : nullptr;
}