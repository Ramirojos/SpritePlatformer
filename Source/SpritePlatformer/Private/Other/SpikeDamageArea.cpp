// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/SpikeDamageArea.h"
#include "Components/BoxComponent.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpikeDamageArea::ASpikeDamageArea():
	DamageValue{1}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageArea=CreateDefaultSubobject<UBoxComponent>(TEXT("Damage area"));
	DamageArea->SetupAttachment(RootComponent);
}

void ASpikeDamageArea::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	//when overlaps with characer cause damage
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);

	if (IsValid(PlayerChar)) {
		UGameplayStatics::ApplyDamage(OtherActor, DamageValue, NULL, this, DamageType);
	}
}

void ASpikeDamageArea::BeginPlay()
{
	Super::BeginPlay();

	DamageArea->SetGenerateOverlapEvents(true);

	//Delegate for damage functionality
	DamageArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASpikeDamageArea::OnBeginOverlapComponentEvent);
	
}




