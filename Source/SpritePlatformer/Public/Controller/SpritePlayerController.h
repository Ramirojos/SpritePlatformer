// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpritePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */


UCLASS()
class SPRITEPLATFORMER_API ASpritePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASpritePlayerController();
	void SetPlayerEnabledState(bool bPlayerEnabled);

protected:

	virtual void BeginPlay() override;

};