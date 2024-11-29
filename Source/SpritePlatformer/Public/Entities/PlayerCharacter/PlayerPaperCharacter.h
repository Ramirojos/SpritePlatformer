// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
//#include "Interfaces/PickupInterface.h"
#include "PlayerPaperCharacter.generated.h"



////*//////continue with implementatioon of interfaces.
//the player inherits from the itnerface
//the item includes from cpp the interfacce
//

class ASpritePickup;
class APlatformerGameMode;
class AHealthPickup;
class APointsPickup;
class ASpritePlayerController;
class UCameraComponent;
class UCapsuleComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UPaperFlipbook;

UCLASS()
class SPRITEPLATFORMER_API APlayerPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
public:

	APlayerPaperCharacter();

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	//Health and points setup

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; };

	UFUNCTION(BlueprintCallable)
	float GetScore() const { return Score; };

	UFUNCTION(BlueprintCallable)
	void AddHealth(float HealthToAdd);

	UFUNCTION(BlueprintCallable)
	void AddPoints(float PointsToAdd);
	
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
	
	UFUNCTION(BlueprintCallable)
	bool IsAlive(float CurrentHealth);

	ASpritePlayerController* GetPlayerController() const { return PlayerController; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DamageSound;
	
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
	

	///******* Aniation related properties *******///

	//Actions liked to sprite animations on the BP
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
	
	//Update player position
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

	ASpritePlayerController* PlayerController;

	APlatformerGameMode* PlatformerGameMode;

	APlayerPaperCharacter* PlayerChar;
};
