// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/AttackCollisionPool.h"
#include "Collision/AttackCollision.h"

const int32 UAttackCollisionPool::AttackCollisionPoolNum = 256;

void UAttackCollisionPool::BeginPlay()
{
    AttackCollisions.Empty();

    TObjectPtr<AAttackCollision> atkColl;
    for (int32 idx = 0; idx < AttackCollisionPoolNum; idx++)
    {
        atkColl = NewObject<AAttackCollision>();
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

