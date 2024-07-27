// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/MSGOGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MSGOUIManager.h"

void AMSGOGameState::BeginPlay()
{
    UIManager = NewObject<UMSGOUIManager>();

    //UIManager->SetupHPGauge(100);
}