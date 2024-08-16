// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MSGOHud.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameState/MSGOGameState.h"
#include "MyHudWidget.h"
#include "UI/MSGOUIManager.h"

void AMSGOHud::BeginPlay()
{
    // WidgetBlueprint‚ÌƒNƒ‰ƒX‚ğæ“¾
    FString path = TEXT("/Game/UI/Widget/WBP_MSGOHud.WBP_MSGOHud_C");
    TSubclassOf<UMyHudWidget> widgetClass = TSoftClassPtr<UMyHudWidget>(FSoftObjectPath(*path)).LoadSynchronous();

    APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (widgetClass && playerController)
    {
        // Widget‚ğì¬
        UIRef = Cast<UMyHudWidget>(UWidgetBlueprintLibrary::Create(GetWorld(), widgetClass, playerController));
   
        // ViewPort‚É’Ç‰Á
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