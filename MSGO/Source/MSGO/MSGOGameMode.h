// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MSGOGameMode.generated.h"

UCLASS(minimalapi)
class AMSGOGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMSGOGameMode();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	void PostLogin(APlayerController* NewPlayer) override;

	FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

	void Logout(AController* Exiting) override;

};



