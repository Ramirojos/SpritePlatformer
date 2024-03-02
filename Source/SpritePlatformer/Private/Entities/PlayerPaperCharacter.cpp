// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/PlayerPaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


APlayerPaperCharacter::APlayerPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//Setting Capsule component properties
	ACharacter::GetCapsuleComponent()->SetCapsuleHalfHeight(14.0f);
	ACharacter::GetCapsuleComponent()->SetCapsuleRadius(11.0f);

	//Setting Spring Arm component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->AddRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CameraBoom->TargetArmLength = 300.0f;
	//CameraBoom->bUsePawnControlRotation = true;
	
	//Setting Camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

void APlayerPaperCharacter::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();

	if (GetController() && (DirectionValue != 0.f)) 
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}

}

void APlayerPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{	//Move Backwards and Forward
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaperCharacter::Move);
	
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}


