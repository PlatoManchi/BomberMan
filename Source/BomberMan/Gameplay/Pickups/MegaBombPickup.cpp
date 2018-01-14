// Fill out your copyright notice in the Description page of Project Settings.

#include "MegaBombPickup.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/Weapon/BombPlacerComponent.h"

AMegaBombPickup::AMegaBombPickup() :
	IncrementCount(2.0f)
{

}

void AMegaBombPickup::PickedUpBy(ABomberManCharacter* Character)
{
	UBombPlacerComponent* bombplacerComponent = Character->GetBombPlacerComponent();

	// Increment the explosion length
	if (bombplacerComponent)
	{
		bombplacerComponent->SetExplosionLength(bombplacerComponent->GetExplosionLength() + IncrementCount);
	}

	Super::PickedUpBy(Character);
}