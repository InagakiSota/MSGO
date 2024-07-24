// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MSGOHud.generated.h"

class UMyHudWidget;

/**
 * 
 */
UCLASS()
class MSGO_API AMSGOHud : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMyHudWidget> UIRef;
};
