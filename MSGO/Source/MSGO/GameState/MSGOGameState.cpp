// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/MSGOGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MSGOUIManager.h"
#include "Characters/MSGOCharacter.h"

void AMSGOGameState::BeginPlay()
{
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
}