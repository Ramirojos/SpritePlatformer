// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthPickup.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Kismet/GameplayStatics.h"

AHealthPickup::AHealthPickup() :
	HealthValue{1} {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase>PickupSoundObject(TEXT("/Script/Engine.SoundWave'/Game/Audio/sounds/Health.Health'"));
	if (IsValid(PickupSoundObject.Object))
	{
		PickupSound = PickupSoundObject.Object;
	}
}

void AHealthPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
		
	//check if the cast is successful, if it is, then call SetHealth from 
	//PlayerCharacter	
	if (IsValid(PlayerChar)) {
		
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		PlayerChar->AddHealth(HealthValue);
		Destroy();
	}
}

