// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
 * 
 */

class APlayerPaperCharacter;
class ASpritePlayerController;
class APointsPickup;

UCLASS()
class SPRITEPLATFORMER_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);
	
	int GetPointsPickupCount();
		
	//display end of game win/loose
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
protected:

	virtual void BeginPlay() override;

	//display start of game
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:

	APlayerPaperCharacter* PlayerChar;
	ASpritePlayerController* SpriteController;

	TArray<AActor*> PointsPickups;
	
	float StartDelay = 3.0f;
	
	void HandleGameStart();
};
