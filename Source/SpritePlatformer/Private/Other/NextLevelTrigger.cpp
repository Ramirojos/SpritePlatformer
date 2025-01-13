// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/NextLevelTrigger.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "GameMode/PlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"


ANextLevelTrigger::ANextLevelTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Triger Area"));
	Levels = { "Level1", "Level2", "Level3"};

	NextLevelSound = CreateDefaultSubobject<USoundBase>(TEXT("Next Level Sound"));
}


void ANextLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerArea->SetGenerateOverlapEvents(true);
	
	//Delegate for Level transition functionality
	TriggerArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANextLevelTrigger::OnBeginOverlapComponentEvent);
}

//When overlapped and point pickups on level reaches 0 then trigger the level transition
void ANextLevelTrigger::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
	APlatformerGameMode* GameMode = (APlatformerGameMode*)GetWorld()->GetAuthGameMode();

	if (IsValid(PlayerChar) && IsValid(GameMode)) {
		if (GameMode->GetPointsPickupCount() == 0) {
			
			UGameplayStatics::PlaySound2D(this, NextLevelSound, 1, 1, 0, NULL, this ,true);

			//timer to transition to next level
			FTimerManager& TimerManager = GetWorldTimerManager();
			FTimerHandle TimerHandle;

			TimerManager.SetTimer(TimerHandle, this, &ANextLevelTrigger::SwitchLevel, 1.75, false);
		}
	}
}

//Change levels when reaching the collision box
void ANextLevelTrigger::SwitchLevel()
{
	//get level name and set it up to transition
	FString current = GetWorld()->GetMapName();
	current.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	for (int i = 0; i < Levels.Num(); i++) {

		//At wich index the name matches the level name 
		if (current == Levels[i]) {
			UGameplayStatics::OpenLevel(GetWorld(), FName(Levels[i + 1]));
		}
	}
}

