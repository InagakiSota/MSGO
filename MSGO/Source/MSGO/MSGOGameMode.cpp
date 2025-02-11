// Copyright Epic Games, Inc. All Rights Reserved.

#include "MSGOGameMode.h"
#include "Characters/MSGOCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/MSGOHud.h"
#include "GameState/MSGOGameState.h"
#include "Controller/MSGOPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

AMSGOGameMode::AMSGOGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Robo/Blueprint/Robo000"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


	GameStateClass = AMSGOGameState::StaticClass();

	HUDClass = AMSGOHud::StaticClass();

	PlayerControllerClass = AMSGOPlayerController::StaticClass();

}

void AMSGOGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UKismetSystemLibrary::PrintString(this, TEXT("AMSGOGameMode::InitGame"));
}

void AMSGOGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	UKismetSystemLibrary::PrintString(this, TEXT("AMSGOGameMode::PreLogin"));

}

void AMSGOGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 playerNum = GetNumPlayers();

	AMSGOCharacter* character = NewPlayer->GetPawn<AMSGOCharacter>();
	if (character)
	{
		FMachineTeamID teamID;
		teamID.TeamID = playerNum%2 == 1 ? ETeamID::TeamA : ETeamID::TeamB;
		teamID.MachineNum = (playerNum - 1) / 2;

		character->MachineTeamID = teamID;
	}
	
	UKismetSystemLibrary::PrintString(this, FString::FromInt(GetNumPlayers()));

}

FString AMSGOGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	UKismetSystemLibrary::PrintString(this, TEXT("AMSGOGameMode::InitNewPlayer"));

}

void AMSGOGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UKismetSystemLibrary::PrintString(this, TEXT("AMSGOGameMode::Logout"));

}


