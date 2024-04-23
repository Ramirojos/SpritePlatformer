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

	UFUNCTION(BlueprintPure, Category = "Coins")
	virtual int32 GetCrystals() const;

	UFUNCTION(BlueprintCallable, Category = "Coins")
	virtual void SetCrystals(int32 newCrystals);

	virtual void StartPlay();

private:

	UPROPERTY()
	int32 CrystalsCount;

	UPROPERTY()
	int32 PlayerHealt;
};
