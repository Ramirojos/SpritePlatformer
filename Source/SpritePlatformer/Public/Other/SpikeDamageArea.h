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
	// Sets default values for this actor's properties
	ASpikeDamageArea();

	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DamageArea;

	UPROPERTY(VisibleAnywhere)
	float DamageValue;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;
};
