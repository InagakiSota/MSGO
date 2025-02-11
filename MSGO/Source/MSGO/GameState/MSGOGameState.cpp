// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/MSGOGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MSGOUIManager.h"
#include "Characters/MSGOCharacter.h"
#include "Collision/AttackCollisionPool.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerState.h"

void AMSGOGameState::BeginPlay()
{
    Super::BeginPlay();

    UIManager = NewObject<UMSGOUIManager>();

    if (!UIManager)
    {
        return;
    }

    //for (APlayerState* PlayerState : this->PlayerArray)
    //{
    //    if (PlayerState)
    //    {
    //        //FString Name;
    //        //PlayerState->GetPlayerController()->GetCharacter()->GetName(Name);
    //        UKismetSystemLibrary::PrintString(this, PlayerState->GetPlayerName());

    //        APlayerController* controller = PlayerState->GetPlayerController();
    //        if (controller)
    //        {
    //            FString name;
    //            controller->GetName(name);

    //            UKismetSystemLibrary::PrintString(this, name);
    //        }
    //    }
    //}

    //

    if (AMSGOCharacter* msgoChara = Cast<AMSGOCharacter>(UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0)))
    {
        UGameInstance* instance = this->GetWorld()->GetGameInstance();
        if (instance)
        {
            //instance->GetNumLocalPlayers
        }

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

// 自身の取得処理
AMSGOGameState* AMSGOGameState::Get(const UObject* WorldContextObject)
{
    UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    return World ? Cast<AMSGOGameState>(World->GetGameState()) : nullptr;
}

// 攻撃コリジョンプールから攻撃コリジョンを取得
AAttackCollision* AMSGOGameState::GetAttackCollisionFromPool()
{
    if (!AttackCollisionPool)
    {
        return nullptr;
    }

    return AttackCollisionPool->GetAttackCollision();
}
