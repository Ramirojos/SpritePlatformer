// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/PlatformerGameMode.h"
#include "Entities/PlayerPaperCharacter.h"
#include "GameState/PlatformerGameState.h"


APlatformerGameMode::APlatformerGameMode()
	:CrystalsCount{0},
	PlayerHealth{3}
{}

int32 APlatformerGameMode::GetCrystals() const
{
	
	return CrystalsCount;
}

void APlatformerGameMode::SetCrystals(int32 newCrystals)
{
	CrystalsCount = newCrystals;
}

int32 APlatformerGameMode::GetHealth() const
{
	return PlayerHealth;
}

void APlatformerGameMode::SetHealth(int32 newHealth)
{
	PlayerHealth = newHealth;
}

void APlatformerGameMode::StartPlay()
{
	Super::StartPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("STartPlay called"));
	GetWorld()->GetAuthGameMode()->GetGameState<APlatformerGameState>()->CrystalsCount = 150;;
}



