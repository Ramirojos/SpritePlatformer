// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPRITEPLATFORMER_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	APlatformerGameMode();

	virtual ~APlatformerGameMode() = default;

	UFUNCTION(BlueprintPure, Category = "Crystals")
	virtual int32 GetCrystals() const;

	UFUNCTION(BlueprintCallable, Category = "Crystals")
	virtual void SetCrystals(int32 newCrystals);


	UFUNCTION(BlueprintPure, Category = "Health")
	virtual int32 GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void SetHealth(int32 newHealth);


	virtual void StartPlay();

private:

	UPROPERTY()
	int32 CrystalsCount;

	UPROPERTY()
	int32 PlayerHealth;
};
