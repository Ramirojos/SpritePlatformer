// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthPickup.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Kismet/GameplayStatics.h"

AHealthPickup::AHealthPickup() :
	HealthValue{1} {
	PrimaryActorTick.bCanEverTick = false;

	//Assign sound file to PickupSound Variable
	static ConstructorHelpers::FObjectFinder<USoundBase>PickupSoundObject(TEXT("/Script/Engine.SoundWave'/Game/Audio/sounds/Health.Health'"));
	if (IsValid(PickupSoundObject.Object))
	{
		PickupSound = PickupSoundObject.Object;
	}
}


//On overlap chack if player character is valid and then adds one to the current player's healt value, plays a sound queue and destroys the pickup.
void AHealthPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
		
	if (IsValid(PlayerChar)) {
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		PlayerChar->AddHealth(HealthValue);
		Destroy();
	}
}

