// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Controller/SpritePlayerController.h"
#include "Entities/Enemies/EnemyPaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameMode/PlatformerGameMode.h"
#include "Items/HealthPickup.h"
#include "Items/PointsPickup.h"
//#include "Items/SpritePickup.h"
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
	
	//Jump properties
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->AirControlBoostMultiplier = 100.f;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 100.0;
	JumpMaxCount = 2;

	//sound queue
	static ConstructorHelpers::FObjectFinder<USoundBase>DamageSoundObject(TEXT("/Script/Engine.SoundWave'/Game/Audio/sounds/hurt.hurt'"));
	if (IsValid(DamageSoundObject.Object))
	{
		DamageSound = DamageSoundObject.Object;
	}
	
}

void APlayerPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	PlayerController = Cast<ASpritePlayerController>(GetController());

	if (IsValid(PlayerController)) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	
	PlatformerGameMode = Cast<APlatformerGameMode> (UGameplayStatics::GetGameMode(this));
}

void APlayerPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePlayer();

	PlayerController->EnableInput(GetPlayerController());
	
}

//What happens when the player reaches 0 lives. 
void APlayerPaperCharacter::HandleDestruction() {
	
	GetCharacterMovement()->DisableMovement();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

//Seting up character movement on a 2D plane.
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

//Related to movement and changing animations in response
void APlayerPaperCharacter::UpdatePlayer()
{
	//Updates animation to match the movement
	UpdateAnimation();

	//Set the direction of the controller
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;

	//We need to check if player is in the air
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
	//First check if the player is alive
		if (bIsAlive)
		{
			//Are we in the air
			if (GetCharacterMovement()->IsFalling()) {
				//Then check for falling speed and set flipbook accordingly
				UPaperFlipbook* DesiredAnimation = (PlayerVelocity.Z < 0.0f) ? JumpFallAnimation : JumpRiseAnimation;
				
				GetSprite()->SetFlipbook(DesiredAnimation);
			}
			else
			{
				//Else, check for ground speed and change the flipbooks
				UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RuningAnimation : IdleAnimation;
				GetSprite()->SetFlipbook(DesiredAnimation);
			}
		}
}

//Action binding to player input
void APlayerPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{	
		//Move Backwards and Forward
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaperCharacter::Move);
		
		// Jumping, already implemented in ACharacter
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

//SetHealth Implementation
void APlayerPaperCharacter::AddHealth(float HealthToAdd)
{	
	Health = FMath::Clamp(Health + HealthToAdd, 0.f, MaxHealth);
}

//IncrementPoints Implementation
void APlayerPaperCharacter::AddPoints(float PointsToAdd)
{
	Score += PointsToAdd;
}

//Manage what happens when the player takes damage
float APlayerPaperCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health= FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);
	UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation());
	if (!IsAlive(Health)) {

		//Character death
		GetSprite()->SetFlipbook(DeathAnimation);

		FTimerHandle PlayerDestructionhandle;
		GetWorldTimerManager().SetTimer(PlayerDestructionhandle,this, &APlayerPaperCharacter::HandleDestruction, 0.6f, false);

		PlatformerGameMode->ActorDied(UGameplayStatics::GetPlayerPawn(this, 0));
		UGameplayStatics::OpenLevel(this, "GameOver_Screen");

	}

	return DamageAmount;
}

//check for alive condition
bool APlayerPaperCharacter::IsAlive(float CurrentHealth)
{
	if (CurrentHealth <= 0) {
		bIsAlive = false;
		return bIsAlive;
	}
	return bIsAlive;
}
