// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/EndGameTrigger.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/PlatformerGameMode.h"


AEndGameTrigger::AEndGameTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Area"));
	GameOverSound = CreateDefaultSubobject<USoundBase>(TEXT("Game over sound"));
}

void AEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	//Delegate for level transition functionality
	TriggerArea->SetGenerateOverlapEvents(true);
	TriggerArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEndGameTrigger::OnBeginOverlapComponentEvent);
}


//When overlapped and point pickups on level reaches 0 then trigger the Game Over level transition
void AEndGameTrigger::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
	APlatformerGameMode* GameMode = (APlatformerGameMode*)GetWorld()->GetAuthGameMode();

	if (IsValid(PlayerChar) && IsValid(GameMode)) {
		if (GameMode->GetPointsPickupCount() == 0) {

			UGameplayStatics::PlaySound2D(this, GameOverSound, 1, 1, 0, NULL, this, true);

			//timer to transition to next level
			FTimerManager& TimerManager = GetWorldTimerManager();
			FTimerHandle TimerHandle;

			TimerManager.SetTimer(TimerHandle, this, &AEndGameTrigger::ToGameOverMenu, 1.75f, false);
			
		}
	}
}

//Transitions to Game Over level
void AEndGameTrigger::ToGameOverMenu()
{
	APlatformerGameMode* GameMode = (APlatformerGameMode*)GetWorld()->GetAuthGameMode();

	if (IsValid(GameMode) && GameMode->GetPointsPickupCount() == 0)
	{
		UGameplayStatics::OpenLevel(this, "GameOver_Screen");
	}

}

