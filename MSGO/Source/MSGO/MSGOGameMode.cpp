// Copyright Epic Games, Inc. All Rights Reserved.

#include "MSGOGameMode.h"
#include "MSGOCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMSGOGameMode::AMSGOGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Robo/Blueprint/Robo000"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
