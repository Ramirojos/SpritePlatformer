// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextLevelTrigger.generated.h"

class UBoxComponent;

UCLASS()
class SPRITEPLATFORMER_API ANextLevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANextLevelTrigger();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);

	void SwitchLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerArea;

private:
	TArray<FString> levels;


};
