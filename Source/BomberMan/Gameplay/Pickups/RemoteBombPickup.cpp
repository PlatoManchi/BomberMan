// Fill out your copyright notice in the Description page of Project Settings.

#include "RemoteBombPickup.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/Weapon/RemoteBombPlacerComponent.h"

ARemoteBombPickup::ARemoteBombPickup() :
	MaxPowerupTime(10.0f)
{

}

void ARemoteBombPickup::PickedUpBy_Implementation(ABomberManCharacter* Character)
{
	UBombPlacerComponent* bombPlacer = Character->SetBombPlacerClass(URemoteBombPlacerComponent::StaticClass());
	URemoteBombPlacerComponent* remoteBombPlacer = Cast<URemoteBombPlacerComponent>(bombPlacer);
	// Set the timer.
	if (remoteBombPlacer)
	{
		remoteBombPlacer->SetMaxPowerupTime(MaxPowerupTime);
	}

	if (Character->OnRemoteBombPickup.IsBound())
	{
		Character->OnRemoteBombPickup.Broadcast(MaxPowerupTime);
	}

	Super::PickedUpBy_Implementation(Character);
}