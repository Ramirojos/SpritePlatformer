// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "PlayerPaperCharacter.generated.h"

class UCapsuleComponent;
class UCameraComponent;
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	//Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputMappingContext* PlayerMappingContext;

	//Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputAction* MoveAction;

	//Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputAction* LookAction;

	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = input)
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* RuningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* JumpRiseAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* JumpFallAnimation;

	//Functions called for Inputs
	void Move(const FInputActionValue& Value);


	void UpdatePlayer();

	//Update the animation when input changes
	void UpdateAnimation();

private:

	//Character Components
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

};
