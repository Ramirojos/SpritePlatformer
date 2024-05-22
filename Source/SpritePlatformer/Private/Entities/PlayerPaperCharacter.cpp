// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/PlayerPaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AttributesComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
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


APlayerPaperCharacter::APlayerPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	//Setting Capsule component properties
	
	ACharacter::GetCapsuleComponent()->SetCapsuleHalfHeight(12.0f);
	ACharacter::GetCapsuleComponent()->SetCapsuleRadius(12.0);
	

	//ColisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Component"));
	//SetRootComponent(ColisionCapsule);
	//ColisionCapsule->SetCapsuleHalfHeight(12.0f);
	//ColisionCapsule->SetCapsuleRadius(12.0f);
	//
	////Capsule collision
	//ColisionCapsule->SetGenerateOverlapEvents(true);
	//ColisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//ColisionCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	//ColisionCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	//Setting Spring Arm component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->AddRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CameraBoom->TargetArmLength = 250.0f;

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
	DieAnimation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Die Anim"));
	//Attribute construction
	Attributes = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attribute Component"));
}


void APlayerPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
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

	if (Controller) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);		

		//add Movement
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementVector.X);
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), MovementVector.Y);
	}
}

//realted to movement and changing animations in response
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
	if (Attributes->IsAlive() == true)
	{
	//are we in the air
		if (GetCharacterMovement()->IsFalling()) {
			//then check for falling speed and set flipbook accordingly
			UPaperFlipbook* DesiredAnimation = (PlayerVelocity.Z < 0.0f) ? JumpFallAnimation : JumpRiseAnimation;
			GetSprite()->SetFlipbook(DesiredAnimation);
		}
		else 
		{
			//else, check for ground speed and change the flipbooks
			UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RuningAnimation : IdleAnimation;
			GetSprite()->SetFlipbook(DesiredAnimation);
		}
	}
	else 
	{
		UPaperFlipbook* DesiredAnimation = DieAnimation;
		GetSprite()->SetFlipbook(DesiredAnimation);
		Delay
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
	{	//Move Backwards and Forward
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaperCharacter::Move);
	
		// Jumping, already implemented in ACharacter
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

//used to tell the player character  wich item is overlapping with
void APlayerPaperCharacter::SetOverlappingItem(ASpritePickup* Item)
{
	OverlappingItem = Item;
}

//Implementation of the pickup interface
void APlayerPaperCharacter::SetHealth(AHealthPickup* HealthPickup)
{
	if (Attributes && HealthPickup) 
	{
		Attributes->AddHealth(HealthPickup->GetHealth());
	}
}

void APlayerPaperCharacter::AddPoints(APointsPickup* PointsPickup)
{
	if (Attributes && PointsPickup)
	{
		Attributes->AddPoints(PointsPickup->GetPoints());
		Attributes->AddHealth(-2);
		UE_LOG(LogTemp, Warning, TEXT("Points added %d"), PointsPickup->GetPoints());
		UE_LOG(LogTemp, Warning, TEXT("Current Points %d"), Attributes->GetPoints());
	}
}

