// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlatformerGameMode.h"
#include "Controller/SpritePlayerController.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Items/PointsPickup.h" 
#include "Kismet/GameplayStatics.h"



//Handles functionality when the playable levels start.
void APlatformerGameMode::HandleGameStart()
{
	SpriteController = Cast<ASpritePlayerController>(UGameplayStatics::GetPlayerController(this, 0));

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

//What happens when the Player Actor dies
void APlatformerGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerChar) {
		PlayerChar->HandleDestruction();
	}
}

void APlatformerGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Sets the ammount of pickups on level start, used in widgets
	SetinitPickups(GetPointsPickupCount());

	HandleGameStart();
}


//Returns the current ammount of Points Pickup actors present in the level
int APlatformerGameMode::GetPointsPickupCount()
{
	//StaticClass returns the type of UObject instance using the instance->GetClass() function.
	UGameplayStatics::GetAllActorsOfClass(this, APointsPickup::StaticClass(), PointsPickups);
	
	return PointsPickups.Num();
}


void APlatformerGameMode::SetinitPickups(int NumOfPickups) {
	InitPointsPickups = NumOfPickups;
}
