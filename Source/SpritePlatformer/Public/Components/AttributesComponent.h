// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPRITEPLATFORMER_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributesComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void RecieveDamage(int32 Damage);
	bool IsAlive();

	//add to current value
	void AddHealth(int32 HealthtoAdd);
	void AddPoints(int32 PointstoAdd);

	FORCEINLINE int32 GetHealth() const{return Health;};
	FORCEINLINE int32 GetPoints() const {return Points;};

	
	
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Actor attributes")
	int32 Health;

	UPROPERTY(EditAnywhere, Category = "Actor attributes")
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor attributes")
	int32 Points;
};
