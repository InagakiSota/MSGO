// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MSGOGameState.generated.h"

class UMSGOUIManager;

/**
 * 
 */
UCLASS()
class MSGO_API AMSGOGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UMSGOUIManager> UIManager;

public:

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	UMSGOUIManager* GetUIManager()
	{
		return UIManager;
	}
	
};
