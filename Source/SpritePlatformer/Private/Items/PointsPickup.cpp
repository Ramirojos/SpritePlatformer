// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PointsPickup.h"
#include "Entities/PlayerCharacter/PlayerPaperCharacter.h"
#include "GameMode/PlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"

APointsPickup::APointsPickup() :
	PointsValue{10} {
	PrimaryActorTick.bCanEverTick = false;

	//Assign sound file to PickupSound Variable
	static ConstructorHelpers::FObjectFinder<USoundBase>PickupSoundObject(TEXT("/Script/Engine.SoundWave'/Game/Audio/sounds/coin.coin'"));
	if (IsValid(PickupSoundObject.Object))
	{
		PickupSound = PickupSoundObject.Object;
	}
}

//When overlapping with the Player Character a sound triggers, a point is added to the point's total and a sound queue is played
void APointsPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSwep, const FHitResult& SweepResult)
{
	APlayerPaperCharacter* PlayerChar = Cast<APlayerPaperCharacter>(OtherActor);
	APlatformerGameMode* GameMode = (APlatformerGameMode*)GetWorld()->GetAuthGameMode();

	if (IsValid(PlayerChar)) {
		PlayerChar->AddPoints(PointsValue);
		Destroy();
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		if (IsValid(GameMode))
		{
			int32 NumOFPickups = GameMode->GetPointsPickupCount();
		}
	}
}