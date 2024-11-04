// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthPickup.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"

AHealthPickup::AHealthPickup() :
	HealthValue{1} {
	PrimaryActorTick.bCanEverTick = true;
}

void AHealthPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	//check if the cast is successful, if it is, then call SetHealth from 
	//PlayerCharacter	
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
	
	if (IsValid(PlayerChar)) {
		PlayerChar->AddHealth(HealthValue);
		Destroy();
	}
}

