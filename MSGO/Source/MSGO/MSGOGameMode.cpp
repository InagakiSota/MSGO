// Copyright Epic Games, Inc. All Rights Reserved.

#include "MSGOGameMode.h"
#include "Characters/MSGOCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/MSGOHud.h"
#include "GameState/MSGOGameState.h"

AMSGOGameMode::AMSGOGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Robo/Blueprint/Robo000"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AMSGOHud::StaticClass();

	GameStateClass = AMSGOGameState::StaticClass();
}
