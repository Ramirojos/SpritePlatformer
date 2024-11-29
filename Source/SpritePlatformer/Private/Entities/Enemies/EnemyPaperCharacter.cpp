// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Enemies/EnemyPaperCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"




AEnemyPaperCharacter::AEnemyPaperCharacter():
	DamageValue{1}
{
	GetCapsuleComponent()->SetCapsuleRadius(12.0);
	GetCapsuleComponent()->SetCapsuleHalfHeight(12.0f);
	
	//Boxes dimentions edited on blueprint
	
	//box that checks for a wall, will change character forward direction when so
	FrontCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WallDetection"));
	FrontCollisionBox->SetupAttachment(RootComponent);
	FrontCollisionBox->SetBoxExtent(FVector(4.0f, 5.0f, 6.0f));

	BottomCollisonBox=CreateDefaultSubobject<UBoxComponent>(TEXT("FloorDetection"));
	BottomCollisonBox->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxAcceleration = 300;
	GetCharacterMovement()->MaxWalkSpeed = 300;

	RuningAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Runing Anim"));
	
	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage box"));
	DamageBox->SetupAttachment(RootComponent);
	DamageBox->SetBoxExtent(FVector(0.4f, 0.25f, 0.35f));

}

void AEnemyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Delegate for Turn box functionality
	FrontCollisionBox->SetGenerateOverlapEvents(true);
	FrontCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyPaperCharacter::WallDetectionEvent);

	//Delegate for Bottom detection behaviour
	BottomCollisonBox->SetGenerateOverlapEvents(true);
	BottomCollisonBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AEnemyPaperCharacter::FloorDetectionEvent);

	//Delegate for Damage Box functiomnality
	DamageBox->SetGenerateOverlapEvents(true);
	DamageBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyPaperCharacter::OnBeginColisionDamageEvent);

}

void AEnemyPaperCharacter::Tick(float DeltaTime)
{
	//Character is always moving Forward
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward,0.25f);
}

//When we overlap world static element the we trun the character
void AEnemyPaperCharacter::WallDetectionEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, 
	const FHitResult& SweepResult)
{
	TurnCharacter();
}

//when we end overlapping with floor, turn around
void AEnemyPaperCharacter::FloorDetectionEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TurnCharacter();
}

void AEnemyPaperCharacter::OnBeginColisionDamageEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	AController* EnemyController = GetInstigator()->GetController();
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);

	if (IsValid(PlayerChar)) {
		UGameplayStatics::ApplyDamage(OtherActor, DamageValue, EnemyController, this, DamageType);
	}	
}

//set the actor rotation to 180° of the original
void AEnemyPaperCharacter::TurnCharacter()
{	
	FRotator Direction = GetActorRotation().Add(0.0f, 180.0f, 0.0f);
	SetActorRotation(Direction);
}



