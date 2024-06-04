// Fill out your copyright notice in the Description page of Project Settings.

//
#include "Structs/ParameterStructs.h"

FCharacterStatusParameter::FCharacterStatusParameter()
    : MaxHP(1000)
    , MaxBoostCap(1000)
    , BoostCharge(100)
    , BoostType(EBOOST_TYPE::NORMAL)
    , MaxDownPoint(1000)
    , MaxSpeed(1000)
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
    , BoostConsumption_Avoidance(100)

{
}

FCharacterStatusParameter_TableRow::FCharacterStatusParameter_TableRow()
    : MaxHP(1000)
    , MaxBoostCap(1000)
    , BoostCharge(100)
    , BoostType(EBOOST_TYPE::NORMAL)
    , MaxDownPoint(1000)
    , MaxSpeed(1000)
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
    , BoostConsumption_Avoidance(100)
{

}