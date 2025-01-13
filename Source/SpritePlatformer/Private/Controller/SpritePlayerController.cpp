// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SpritePlayerController.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASpritePlayerController::ASpritePlayerController()
{

}


//Enables/disables input, called in GameMode
void ASpritePlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	
	if (bPlayerEnabled) {
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);
	}
}

void ASpritePlayerController::BeginPlay()
{
	Super::BeginPlay();
}
