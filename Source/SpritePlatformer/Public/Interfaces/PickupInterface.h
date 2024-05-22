// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"


UINTERFACE(MinimalAPI)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPRITEPLATFORMER_API IPickupInterface
{
	GENERATED_BODY()

public:

	virtual void SetOverlappingItem(class ASpritePickup* Item);
			
	virtual void SetHealth(class AHealthPickup* HealthPickup);
	virtual void AddPoints(class APointsPickup* PointsPickup);
	
};
