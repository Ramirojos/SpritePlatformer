// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "EnemyPaperCharacter.generated.h"

/**
 * 
 */
class UAttributesComponent;
class UBoxComponent;
class UPaperFlipbook;
class UStaticMeshComponent;

UCLASS()
class SPRITEPLATFORMER_API AEnemyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
	

public:

	AEnemyPaperCharacter();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
	const FHitResult& SweepResult); 

	//To implement
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	//class AController* EventInstigator, AActor* DamageCauser) override;

	//tuirns the enemy character when overlapping with wall
	void TurnCharacter();

protected:

	virtual void BeginPlay();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* RuningAnimation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* FrontCollisionBox;

private:

	//to implement
	UPROPERTY(VisibleAnywhere)
	UAttributesComponent* Attributes;

	

};
