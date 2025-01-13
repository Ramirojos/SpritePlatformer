// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGameTrigger.generated.h"

class UBoxComponent;
class USoundBase;

UCLASS()
class SPRITEPLATFORMER_API AEndGameTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	AEndGameTrigger();

	UFUNCTION()
	virtual void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep,
		const FHitResult& SweepResult);

	void ToGameOverMenu();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerArea;

private:

	UPROPERTY(EditDefaultsOnly)
	USoundBase* GameOverSound;
};
