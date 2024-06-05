// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributesComponent.h"

UAttributesComponent::UAttributesComponent():
	Health{1},
	MaxHealth{3},
	Points{3}
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	IsAlive();
}

//Calculates the new health value after taking damage
//won't let it go below 0
void UAttributesComponent::RecieveDamage(int32 Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
}

//we check every tick if the healt is health is >0
bool UAttributesComponent::IsAlive(){
	if (Health > 0) 
	{
		return true;
	}
	
	return false;
}

//adds health when overlap with heal pickup
//wont let the value go above max health
void UAttributesComponent::AddHealth(int32 HealthtoAdd)
{
	Health = FMath::Clamp(Health + HealthtoAdd, 0.f, MaxHealth);
}

//simple Setter function for point count
void UAttributesComponent::AddPoints(int32 PointstoAdd)
{
	Points += PointstoAdd;
}

