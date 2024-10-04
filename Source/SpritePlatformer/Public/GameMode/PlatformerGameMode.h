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

UCLASS()
class SPRITEPLATFORMER_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();


private:

	APlayerPaperCharacter* PlayerChar;
	ASpritePlayerController* SpriteController;


	float StartDelay = 3.0f;
	
	void HandleGameStart();
};
