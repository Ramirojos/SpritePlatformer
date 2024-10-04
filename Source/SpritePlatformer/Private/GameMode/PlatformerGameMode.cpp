// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlatformerGameMode.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Controller/SpritePlayerController.h" 
#include "Kismet/GameplayStatics.h"

//what happens when teh Player Actor dies
void APlatformerGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerChar) {
		//check for player controller and if valid disable input
		PlayerChar->HandleDestruction();
		//SpriteController = Cast<ASpritePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		
		if (SpriteController)
		{
			SpriteController->SetPlayerEnabledState(false);
		}
		
	}
}

void APlatformerGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

	
}

void APlatformerGameMode::HandleGameStart()
{
	PlayerChar = Cast<APlayerPaperCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	SpriteController = Cast<ASpritePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//Event to be called from blueprint,
	//will use it to create and manipulate Start Game widget
	StartGame();

	//Disable the input until the timer runs out
	if (SpriteController) {
		SpriteController->SetPlayerEnabledState(false);

		//Handle for SetTimer
		FTimerHandle PlayerEnableTimeHandle;

		//Delegate 
		FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
				SpriteController,
				&ASpritePlayerController::SetPlayerEnabledState,
				true);

		//Overloaded SetTimer function for callback with inputs 
		GetWorldTimerManager().SetTimer(PlayerEnableTimeHandle,
				PlayerEnabledTimerDelegate,
				StartDelay,
				false);
	}
}
