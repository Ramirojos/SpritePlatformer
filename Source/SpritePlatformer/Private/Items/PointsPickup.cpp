// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PointsPickup.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"

APointsPickup::APointsPickup() :
	PointsValue{10} {
	PrimaryActorTick.bCanEverTick = true;
}

void APointsPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	//check if te cast is successful, if it is, then call AddPoints from 
	//PlayerCharacter
	APlayerPaperCharacter* PlayerCahar = Cast<APlayerPaperCharacter>(OtherActor);
	if (PlayerCahar) {
		PlayerCahar->AddPoints(PointsValue);
		Destroy();
	}
}
