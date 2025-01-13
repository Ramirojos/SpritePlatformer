// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SpritePickup.h"
#include "PointsPickup.generated.h"

UCLASS()
class SPRITEPLATFORMER_API APointsPickup : public ASpritePickup
{
	GENERATED_BODY()
public:

	APointsPickup();
	
protected:

	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult) override;

private:

	UPROPERTY(EditAnywhere, Category = "Points Pickup")
	int32 PointsValue;
};
