// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpritePickup.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;

UCLASS()
class SPRITEPLATFORMER_API ASpritePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpritePickup();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult) ;

protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* PickupCapsule;
private:
	
	//flipbook for the pickup children
	UPROPERTY(VisibleAnywhere, Category = Animation)
	UPaperFlipbookComponent* PickupFlipBookComponent;
	

};


