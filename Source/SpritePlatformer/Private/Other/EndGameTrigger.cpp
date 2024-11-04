// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/EndGameTrigger.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "GameMode/PlatformerGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
AEndGameTrigger::AEndGameTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Area"));


}

// Called when the game starts or when spawned
void AEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerArea->SetGenerateOverlapEvents(true);
	TriggerArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEndGameTrigger::OnBeginOverlapComponentEvent);
}

// Called every frame
void AEndGameTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndGameTrigger::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
	APlatformerGameMode* GameMode = (APlatformerGameMode*)GetWorld()->GetAuthGameMode();

	if (IsValid(PlayerChar) && IsValid(GameMode)) {
		if (GameMode->GetPointsPickupCount() == 0) {
			GameMode->GameOver(true);
		}
	}
}

