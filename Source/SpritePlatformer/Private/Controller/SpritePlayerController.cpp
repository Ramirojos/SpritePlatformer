// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SpritePlayerController.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASpritePlayerController::ASpritePlayerController()
{

}


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

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(PlayerContext, 0);


}

void ASpritePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpritePlayerController::Move);
	
	
	// Jumping, already implemented in ACharacter
}
void ASpritePlayerController::Move(const FInputActionValue& InputACtionValue)
{

}
