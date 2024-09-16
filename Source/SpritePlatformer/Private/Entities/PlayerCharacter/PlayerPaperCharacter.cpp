// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Entities/Enemies/EnemyPaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/HealthPickup.h"
#include "Items/PointsPickup.h"
#include "Items/SpritePickup.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"



APlayerPaperCharacter::APlayerPaperCharacter():
	Health{3},
	MaxHealth{3},
	Score{0},
	bIsAlive{true}
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	//Setting Capsule component properties
	GetCapsuleComponent()->SetCapsuleRadius(12.0);
	GetCapsuleComponent()->SetCapsuleHalfHeight(12.0f);
		
	//Setting Spring Arm component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->AddRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CameraBoom->TargetArmLength = 250.0f;
	//CameraBoom->bDoCollisionTest(false);


	//Setting Camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(CameraBoom);

	GetCharacterMovement()->MaxWalkSpeed = 300;
	GetCharacterMovement()->MaxAcceleration = 300;

	//Animation properties		
	IdleAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Idle Anim"));
	RuningAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Runing Anim")); 
	JumpRiseAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Jump RiseAnim"));
	JumpFallAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Jump DownAnim"));
	DeathAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Death Anim"));
	TakeDamageAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Take Damage Anim"));
}


void APlayerPaperCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	UE_LOG(LogTemp, Warning, TEXT("Starting Health: %f"), GetHealth());

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

//Seting up character movement on a 2D plane
void APlayerPaperCharacter::Move(const FInputActionValue& Value)
{
	//Where is forward
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller && bIsAlive) {
		const FRotator Rotation = Controller->GetControlRotation();
	
		const FRotator YawRotation(0, Rotation.Yaw, 0);		

		//add Movement
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementVector.X);
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), MovementVector.Y);
	}
}

//related to movement and changing animations in response
void APlayerPaperCharacter::UpdatePlayer()
{
	//updates animation to match the movement
	UpdateAnimation();

	//set the direction of the controller
	const FVector PlayerVelocity = GetVelocity();
	//units on X axis
	float TravelDirection = PlayerVelocity.X;

	//we need to check if player is in the air
	if (Controller) {
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if(TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

//For changing the sprite we use when moving/jumping/idle
void APlayerPaperCharacter::UpdateAnimation()
{		
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
	//is the velocity of te character greater on ground greater than 0

	//first check if the player is alive
		if (bIsAlive)
		{
			//are we in the air
			if (GetCharacterMovement()->IsFalling()) {
				//then check for falling speed and set flipbook accordingly
				UPaperFlipbook* DesiredAnimation = (PlayerVelocity.Z < 0.0f) ? JumpFallAnimation : JumpRiseAnimation;
				GetCharacterMovement()->AirControl = 0.2f;
				GetSprite()->SetFlipbook(DesiredAnimation);
			}
			else
			{
				//else, check for ground speed and change the flipbooks
				UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RuningAnimation : IdleAnimation;
				GetSprite()->SetFlipbook(DesiredAnimation);
			}
		}
		else {

		}
}


void APlayerPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePlayer();
}

//action binding to player input, used the new enhanced input system
void APlayerPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{	
		//if (bIsAlive) {
			//Move Backwards and Forward
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaperCharacter::Move);
		
			// Jumping, already implemented in ACharacter
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		//}
	}
}

//SetHealth Implementation
void APlayerPaperCharacter::AddHealth(float HealthToAdd)
{	
	Health = FMath::Clamp(Health + HealthToAdd, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health after pickup: %f"), GetHealth());
}

//IncrementPoints Implementation
void APlayerPaperCharacter::AddPoints(float PointsToAdd)
{
	Score += PointsToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Current points after pickup: %f"), GetScore());
}

float APlayerPaperCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//RecieveDamage(DamageAmount); 
	Health= FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);
	
	if(!IsAlive(Health)){
		//character death
		UE_LOG(LogTemp, Warning, TEXT("player dead"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Current Health after taking damage: %f"), GetHealth());
	//UE_LOG(LogTemp, Warning, TEXT("Is Alive %s"), IsAlive(Health) ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Warning, TEXT("Is Alive %s"), bIsAlive? TEXT("true") : TEXT("false"));
	return DamageAmount;
}


bool APlayerPaperCharacter::IsAlive(float CurrentHealth)
{
	if (CurrentHealth <= 0) {
		bIsAlive = false;
		UE_LOG(LogTemp, Warning, TEXT("im dead with Current health %f"), CurrentHealth);
		return bIsAlive;
	}
	UE_LOG(LogTemp, Warning, TEXT("im alive with Current health %f"), CurrentHealth);
	return bIsAlive;
}
