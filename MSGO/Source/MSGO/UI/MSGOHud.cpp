// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MSGOHud.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameState/MSGOGameState.h"
#include "MyHudWidget.h"
#include "UI/MSGOUIManager.h"

void AMSGOHud::BeginPlay()
{
    // WidgetBlueprintのクラスを取得
    FString path = TEXT("/Game/UI/Widget/WBP_MSGOHud.WBP_MSGOHud_C");
    TSubclassOf<UMyHudWidget> widgetClass = TSoftClassPtr<UMyHudWidget>(FSoftObjectPath(*path)).LoadSynchronous();

    APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (widgetClass && playerController)
    {
        // Widgetを作成
        UIRef = Cast<UMyHudWidget>(UWidgetBlueprintLibrary::Create(GetWorld(), widgetClass, playerController));
   
        // ViewPortに追加
        UIRef->AddToViewport(0);
    }

    AMSGOGameState* gameState = Cast<AMSGOGameState>(UGameplayStatics::GetGameState(this));
    if (!gameState)
    {
        return;
    }

    UMSGOUIManager* uiManager = gameState->GetUIManager();
    if (!uiManager)
    {
        return;
    }

    uiManager->SetHudWidget(UIRef);
}