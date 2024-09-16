// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "EnemyPaperCharacter.generated.h"

/**
 * 
 */
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
	virtual void WallDetectionEvent(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
	const FHitResult& SweepResult); 

	UFUNCTION()
	virtual void OnBeginColisionDamageEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void FloorDetectionEvent(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void TurnCharacter();

protected:

	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbook* RuningAnimation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* FrontCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BottomCollisonBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* DamageBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage value")
	float DamageValue;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

private:
};
