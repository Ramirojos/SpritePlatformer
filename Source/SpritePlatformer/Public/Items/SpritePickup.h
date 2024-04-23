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
	void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;



	//variables to set sin movement of the pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UFUNCTION(BlueprintPure)
	float ItemFloatingMovement();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UPaperFlipbookComponent* PickupFlipBookComponent;
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* PickupCapsule;
private:
	


};
