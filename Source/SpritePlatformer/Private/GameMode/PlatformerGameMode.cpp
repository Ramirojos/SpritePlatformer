// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlatformerGameMode.h"
#include "Controller/SpritePlayerController.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Items/PointsPickup.h" 
#include "Kismet/GameplayStatics.h"



void APlatformerGameMode::HandleGameStart()
{
	SpriteController = Cast<ASpritePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//Event to be called from blueprint,
	//will be used to create and manipulate Start Game widget
	StartGame();

	//Disable the input until the timer runs out
	if (IsValid(SpriteController)) {
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

//What happens when the Player Actor dies, could be a player (or an enemy in the future)
void APlatformerGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerChar) {
		PlayerChar->HandleDestruction();
	}
}

void APlatformerGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetinitPickups(GetPointsPickupCount());

	HandleGameStart();
}

int APlatformerGameMode::GetPointsPickupCount()
{
	//StaticClass returns the type of UObject instance using the instance->GetClass() function.
	UGameplayStatics::GetAllActorsOfClass(this, APointsPickup::StaticClass(), PointsPickups);
	
	return PointsPickups.Num();
}


void APlatformerGameMode::SetinitPickups(int NumOfPickups) {
	InitPointsPickups = NumOfPickups;
}
