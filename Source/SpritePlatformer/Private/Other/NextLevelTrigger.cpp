// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/NextLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "GameMode/PlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANextLevelTrigger::ANextLevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Triger Area"));
	levels = { "Level_1", "level_2" };
}

// Called when the game starts or when spawned
void ANextLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerArea->SetGenerateOverlapEvents(true);
	TriggerArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANextLevelTrigger::OnBeginOverlapComponentEvent);
}

// Called every frame
void ANextLevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANextLevelTrigger::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
	APlatformerGameMode* GameMode = (APlatformerGameMode*)GetWorld()->GetAuthGameMode();

	if (IsValid(PlayerChar) && IsValid(GameMode)) {
		if (GameMode->GetPointsPickupCount() == 0) {
			
			FTimerManager& TimerManager = GetWorldTimerManager();
			FTimerHandle TimerHandle;

			TimerManager.SetTimer(TimerHandle, this, &ANextLevelTrigger::SwitchLevel, 1.0f , false);
		}
	}
}

void ANextLevelTrigger::SwitchLevel()
{
	FString current = GetWorld()->GetMapName();
	current.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	for (int i = 0; i < levels.Num(); i++) {

		//At wich index the name matches the level name 
		if (current == levels[i]) {
			UGameplayStatics::OpenLevel(GetWorld(), FName(levels[i + 1]));
		}
	}
}

