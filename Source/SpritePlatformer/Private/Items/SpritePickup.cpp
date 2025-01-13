// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/SpritePickup.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"

ASpritePickup::ASpritePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	//Set the base properties of the capsule and prepping for 
	//Interaction with Player Caharacter
	PickupCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule"));
	SetRootComponent(PickupCapsule);
	PickupCapsule->SetCapsuleHalfHeight(8.0f);
	PickupCapsule->SetCapsuleRadius(8.0f);

	//Sprite setup
	PickupFlipBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("anim"));
	PickupFlipBookComponent->SetupAttachment(PickupCapsule);

}

void ASpritePickup::BeginPlay()
{
	Super::BeginPlay();

	PickupCapsule->SetGenerateOverlapEvents(true);

	//Delegate for Pickup actor overlapping fuctionality
	PickupCapsule->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASpritePickup::OnBeginOverlapComponentEvent);
}


void ASpritePickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
	const FHitResult& SweepResult)
{}

