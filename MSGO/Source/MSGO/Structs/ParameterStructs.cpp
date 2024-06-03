// Fill out your copyright notice in the Description page of Project Settings.

//
#include "Structs/ParameterStructs.h"

FCharacterStatusParameter::FCharacterStatusParameter()
    : MaxHP(1000)
    , MaxBoostCap(1000)
    , BoostCharge(100)
    , MaxDownPoint(1000)
    , MaxSpeed(100)
    , MaxAcceleration(100)
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