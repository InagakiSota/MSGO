// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/AttackCollisionPool.h"
#include "Collision/AttackCollision.h"

const int32 UAttackCollisionPool::AttackCollisionPoolNum = 256;

void UAttackCollisionPool::BeginPlay()
{
    AttackCollisions.Empty();

    TObjectPtr<AAttackCollision> atkColl;
    UWorld* world = this->GetWorld();
    if (!world)
    {
        return;
    }

    for (int32 idx = 0; idx < AttackCollisionPoolNum; idx++)
    {
        atkColl = world->SpawnActor<AAttackCollision>(AAttackCollision::StaticClass());
        if (!atkColl || !IsValid(atkColl))
        {
            continue;
        }

        atkColl->SleepObject();
        AttackCollisions.Add(atkColl);
    }
}

void UAttackCollisionPool::BeginDestroy()
{
    Super::BeginDestroy();

    if (AttackCollisions.IsEmpty())
    {
        return;
    }

    for (int32 idx = 0; idx < AttackCollisionPoolNum; idx++)
    {
        if (!AttackCollisions.IsValidIndex(idx))
        {
            continue;
        }

        if (AttackCollisions[idx] == nullptr)
        {
            continue;
        }

        AttackCollisions[idx]->Destroy();
    }

    AttackCollisions.Empty();
}

// 攻撃コリジョンを取得
AAttackCollision* UAttackCollisionPool::GetAttackCollision() const
{
    for (int32 idx = 0; idx < AttackCollisionPoolNum; idx++)
    {
        // 無効な要素数ならスルー
        if (!AttackCollisions.IsValidIndex(idx))
        {
            continue;
        }

        // Nullならスルー
        if (AttackCollisions[idx] == nullptr || !IsValid(AttackCollisions[idx]))
        {
            continue;
        }

        // 使用中ならスルー
        if (AttackCollisions[idx]->IsActive())
        {
            continue;
        }

        // ここまで来たら返す
        return AttackCollisions[idx];
    }

    return nullptr;
}

UWorld* UAttackCollisionPool::GetWorld() const
{
    UWorld* world = (GetOuter() != nullptr) ? GetOuter()->GetWorld() : GWorld;
    if (world == nullptr)
    {
        world = GWorld;
    }

    return world;
}

