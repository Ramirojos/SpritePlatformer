// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/SpritePickup.h"
#include "Interfaces/PickupInterface.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ASpritePickup::ASpritePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	//set the base properties of the capsule and prepping for 
	//interaction with Player Caharacter
	PickupCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule"));
	SetRootComponent(PickupCapsule);
	PickupCapsule->SetCapsuleHalfHeight(8.0f);
	PickupCapsule->SetCapsuleRadius(8.0f);
	
	//Sprite setup
	PickupFlipBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("anim"));
	PickupFlipBookComponent-> SetupAttachment(PickupCapsule);


}	

void ASpritePickup::BeginPlay()
{
	Super::BeginPlay();

	//we want the capsule PickupCapsule constructed before we setup the collision properties
	PickupCapsule->SetGenerateOverlapEvents(true);

	//setup the responses to colision with component
	//PickupCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//PickupCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	//PickupCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASpritePickup::OnBeginOverlapComponentEvent);
}


void ASpritePickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
	const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface) {
		PickupInterface->SetOverlappingItem(this);
		Destroy();

	}
}

 void ASpritePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


