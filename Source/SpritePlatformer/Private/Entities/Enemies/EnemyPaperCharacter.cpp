// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Enemies/EnemyPaperCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"




AEnemyPaperCharacter::AEnemyPaperCharacter()
{
	GetCapsuleComponent()->SetCapsuleRadius(12.0);
	GetCapsuleComponent()->SetCapsuleHalfHeight(12.0f);
	
	//Boxes dimentions edited on blueprint
	
	//box that checks for a wall, will change directios when so
	FrontCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WallDetection"));
	FrontCollisionBox->SetupAttachment(RootComponent);
	
	RuningAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Runing Anim"));
	
	GetCharacterMovement()->MaxAcceleration = 300;
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void AEnemyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	FrontCollisionBox->SetGenerateOverlapEvents(true);
	FrontCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyPaperCharacter::OnBeginOverlapComponentEvent);
}

void AEnemyPaperCharacter::Tick(float DeltaTime)
{
	//Character is always moving Forward
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward,0.25f);
}

void AEnemyPaperCharacter::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, 
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("On component overlap called"));
	TurnCharacter();
}


void AEnemyPaperCharacter::TurnCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("TurnCharacter"));
	FRotator Direction = GetActorRotation().Add(0.0f, 180.0f, 0.0f);
	SetActorRotation(Direction);
}



