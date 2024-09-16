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

	
	//Health and points setup

	UFUNCTION(BlueprintCallable)
	float GetHealth() { return Health; };

	UFUNCTION(BlueprintCallable)
	float GetScore() { return Score; };

	UFUNCTION(BlueprintCallable)
	//void AddHealth(class AHealthPickup* HealthPickup);
	void AddHealth(float HealthToAdd);

	UFUNCTION(BlueprintCallable)
	void AddPoints(float PointsToAdd);
	
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
	
	bool IsAlive(float CurrentHealth);
	
protected:

	virtual void BeginPlay() override;

	/******* Movement related properties ******/
	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

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
	UPaperFlipbook* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* TakeDamageAnimation;

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
	float Health;

	UPROPERTY(VisibleAnywhere)
	float Score;

	UPROPERTY(VisibleAnywhere)
	bool bIsAlive;
};
