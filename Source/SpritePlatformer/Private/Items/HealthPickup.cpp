// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthPickup.h"
#include "Interfaces/PickupInterface.h"

AHealthPickup::AHealthPickup() :HealthValue{1} {
	PrimaryActorTick.bCanEverTick = true;
}

void AHealthPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	//check if te cast is successful, if it is, then call SetHealth from 
	//PlayerCharacter
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface) {
		
		PickupInterface->SetHealth(this);
		Destroy();
	}
}

