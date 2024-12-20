﻿// Fill out your copyright notice in the Description page of Project Settings.

//
#include "Structs/ParameterStructs.h"

FCharacterStatusParameter::FCharacterStatusParameter()
    : MaxHP(1000)
    , MaxBoostCap(1000)
    , BoostCharge(100)
    , BoostType(EBoostType::Normal)
    , MaxDownPoint(1000)
    , InitSpeed(800)
    , MaxSpeed(1000)
    , CrusingSpeed(900)
    , TransitionFrame_MaxSpeed(60)
    , SustainedFrame_MaxSpeed(180)
    , TransitionFrame_CrusingSpeed(60)
    , MaxWalkSpeed(500)
    , MaxAcceleration(10000)
    , MaxWalkAcceleration(2048)
    , ReturnValue(100)
    , MachineCost(100)
    , DamageCutRate_Bullet(0.f)
    , DamageCutRate_Bomb(0.f)
    , DamageCutRate_Beam(0.f)
    , DamageCutRate_Combat(0.f)
    , AssistModuleSlotNum(10)
    , JumpRiseHeight(100)
    , JumpRiseSpeed(100)
    , BoostGaugeDecrement_BeginBoostDash(50)
    , BoostGaugeDecrement_BoostDash(5)
    , BoostGaugeDecrement_Rising(2)
    , BoostGaugeIncrement_Normal(10)
    , BoostGaugeIncrement_OverHeat(5)
    , BoostGaugeDecrement_Avoidance(100)
    , BeginBoostChargeFrame(120)

{
}

FCharacterStatusParameter_TableRow::FCharacterStatusParameter_TableRow()
    : MaxHP(1000)
    , MaxBoostCap(1000)
    , BoostCharge(100)
    , BoostType(EBoostType::Normal)
    , MaxDownPoint(1000)
    , InitSpeed(800)
    , MaxSpeed(1000)
    , CrusingSpeed(900)
    , TransitionFrame_MaxSpeed(60)
    , SustainedFrame_MaxSpeed(180)
    , TransitionFrame_CrusingSpeed(60)
    , MaxWalkSpeed(500)
    , MaxAcceleration(10000)
    , MaxWalkAcceleration(2048)
    , ReturnValue(100)
    , MachineCost(100)
    , DamageCutRate_Bullet(0.f)
    , DamageCutRate_Bomb(0.f)
    , DamageCutRate_Beam(0.f)
    , DamageCutRate_Combat(0.f)
    , AssistModuleSlotNum(10)
    , JumpRiseHeight(100)
    , JumpRiseSpeed(100)
    , BoostGaugeDecrement_BeginBoostDash(50)
    , BoostGaugeDecrement_BoostDash(5)
    , BoostGaugeDecrement_Rising(2)
    , BoostGaugeIncrement_Normal(10)
    , BoostGaugeIncrement_OverHeat(5)
    , BoostGaugeDecrement_Avoidance(100)
    , BeginBoostChargeFrame(120)
{

}

FAttackCollisionPowerParameter::FAttackCollisionPowerParameter()
    : BaseAttackPower(0)
    , DownPoint(0)
    , AttackType(EAttackType::Bullet)
{

}

FAttackCollisionParameter::FAttackCollisionParameter()
    : CollisionSize(FVector::ZeroVector)
    , MaxHitAcotrNum(1)
    , LiveMaxFrame(60)
{

}

FAttackCollisionMovementParameter::FAttackCollisionMovementParameter()
    : StartPos(FVector::ZeroVector)
    , StartRot(FRotator::ZeroRotator)
    , MoveDir(FVector::ZeroVector)
    , MoveSpeed(0.f)
{

}

FDamageCollisionParameter::FDamageCollisionParameter()
    : CollisionSize(FVector::ZeroVector)
{

}