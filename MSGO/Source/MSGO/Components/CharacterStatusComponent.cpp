// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/StaticDataManager.h"

// Sets default values for this component's properties
UCharacterStatusComponent::UCharacterStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	FCharacterStatusParameter parameterStatus;
	UStaticDataManager::GetCharacterParameterData(this, 1, parameterStatus);

	UKismetSystemLibrary::PrintString(this, parameterStatus.MachineName.ToString());

}


// Called every frame
void UCharacterStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

