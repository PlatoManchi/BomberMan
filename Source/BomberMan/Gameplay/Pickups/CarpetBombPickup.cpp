// Fill out your copyright notice in the Description page of Project Settings.

#include "CarpetBombPickup.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/BomberManPlayerState.h"

ACarpetBombPickup::ACarpetBombPickup() :
	IncrementAmount(2.0f)
{

}

void ACarpetBombPickup::PickedUpBy_Implementation(ABomberManCharacter* Character)
{
	ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(Character->GetController()->PlayerState);

	// Increment the available bombs to player.
	if (playerState)
	{
		playerState->MaxBombsAvailable += IncrementAmount;
		playerState->CurrentBombsAvailable += IncrementAmount;
	}

	Super::PickedUpBy_Implementation(Character);
}
