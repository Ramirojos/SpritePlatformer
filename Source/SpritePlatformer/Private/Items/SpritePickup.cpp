// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/SpritePickup.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ASpritePickup::ASpritePickup()
	:Amplitude{0.25f},
	TimeConstant {5.f}
{
	PrimaryActorTick.bCanEverTick = true;

	//set the base properties of the capsule and prepping for 
	//interaction with Player Caharacter
	PickupCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule"));
	SetRootComponent(PickupCapsule);
	PickupCapsule->SetCapsuleHalfHeight(8.0f);
	PickupCapsule->SetCapsuleRadius(8.0f);
	PickupCapsule->SetGenerateOverlapEvents(true);

	//setup the responses to colision with component
	PickupCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASpritePickup::OnBeginOverlapComponentEvent);

	PickupFlipBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("anim"));
	PickupFlipBookComponent-> SetupAttachment(PickupCapsule);


}	

void ASpritePickup::BeginPlay()
{
	Super::BeginPlay();
	
}


//sets sin movement of the item
float ASpritePickup::ItemFloatingMovement()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

void ASpritePickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
	const FHitResult& SweepResult) 
{

	//if(!Cast<ACharacter>(OtherActor)) return;
	if (OtherActor == nullptr) {
		
		return;
	}

	Destroy();
}
 void ASpritePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
	ItemFloatingMovement();

}

