// Fill out your copyright notice in the Description page of Project Settings.

#include "MegaBombPickup.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/Weapon/BombPlacerComponent.h"

AMegaBombPickup::AMegaBombPickup() :
	IncrementAmount(2.0f)
{

}

void AMegaBombPickup::PickedUpBy_Implementation(ABomberManCharacter* Character)
{
	UBombPlacerComponent* bombplacerComponent = Character->GetBombPlacerComponent();

	// Increment the explosion length
	if (bombplacerComponent)
	{
		bombplacerComponent->SetExplosionLength(bombplacerComponent->GetExplosionLength() + IncrementAmount);
	}

	Super::PickedUpBy_Implementation(Character);
}