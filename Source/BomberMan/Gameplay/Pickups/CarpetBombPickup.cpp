// Fill out your copyright notice in the Description page of Project Settings.

#include "CarpetBombPickup.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/BomberManPlayerState.h"

ACarpetBombPickup::ACarpetBombPickup() :
	IncrementAmount(2.0f)
{

}

void ACarpetBombPickup::PickedUpBy(ABomberManCharacter* Character)
{
	ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(Character->GetController()->PlayerState);

	if (playerState)
	{
		playerState->MaxBombsAvailable += IncrementAmount;
		playerState->CurrentBombsAvailable += IncrementAmount;
	}

	Super::PickedUpBy(Character);
}