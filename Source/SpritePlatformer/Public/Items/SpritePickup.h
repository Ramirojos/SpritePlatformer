// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpritePickup.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;
class USoundBase;

UCLASS()
class SPRITEPLATFORMER_API ASpritePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpritePickup();

	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* PickupCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PickupSound;
private:
	
	//Flipbook for the pickup children
	UPROPERTY(VisibleAnywhere, Category = Animation)
	UPaperFlipbookComponent* PickupFlipBookComponent;
	

};


