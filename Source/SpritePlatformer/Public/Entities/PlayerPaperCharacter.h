// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "Interfaces/PickupInterface.h"
#include "PlayerPaperCharacter.generated.h"



////*//////continue with implementatioon of interfaces.
//the player inherits from the itnerface
//the item includes from cpp the interfacce
//

class ASpritePickup;
class AHealthPickup;
class APointsPickup;
class UAttributesComponent;
class UCameraComponent;
class UCapsuleComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UPaperFlipbook;

UCLASS()
class SPRITEPLATFORMER_API APlayerPaperCharacter : public APaperCharacter, public IPickupInterface
{
	GENERATED_BODY()
public:

	APlayerPaperCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetOverlappingItem(class ASpritePickup* Item) override;
	
	virtual void SetHealth(class AHealthPickup* HealthPickup) override;
	virtual void AddPoints(class APointsPickup* PointsPickup) override;

protected:

	virtual void BeginPlay() override;

	/******* Movement related properties ******/

	//Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputMappingContext* PlayerMappingContext;

	//Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputAction* MoveAction;

	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputAction* JumpAction;
	

	///******* Anmiation relted properties *******///

	//Actions to be liked to wich link the sprite animations on the BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* RuningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* JumpRiseAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* JumpFallAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* DieAnimation;
	
	//Overlapping component
	UPROPERTY(VisibleInstanceOnly)
	ASpritePickup* OverlappingItem;

	///*************///

	//Functions called for Inputs
	void Move(const FInputActionValue& Value);
	
	//update player position
	void UpdatePlayer();

	//Update the animation when input changes
	void UpdateAnimation();

private:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UAttributesComponent* Attributes;

};
