// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeDamageArea.generated.h"

class UBoxComponent;

UCLASS()
class SPRITEPLATFORMER_API ASpikeDamageArea : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpikeDamageArea();

	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);
	
protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DamageArea;

	UPROPERTY(VisibleAnywhere)
	float DamageValue;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;
};
