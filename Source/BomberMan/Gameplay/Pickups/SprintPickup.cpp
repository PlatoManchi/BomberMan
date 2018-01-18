// Fill out your copyright notice in the Description page of Project Settings.

#include "SprintPickup.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/BomberManPlayerState.h"

// Engine includes
#include "GameFramework/CharacterMovementComponent.h"

ASprintPickup::ASprintPickup() : 
	SpeedMultiplier(2.0f)
{
}

void ASprintPickup::PickedUpBy_Implementation(ABomberManCharacter* Character)
{
	ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(Character->GetController()->PlayerState);

	// Boost the speed of character if not boosted
	if (playerState && !playerState->IsSpeedBoost)
	{
		playerState->IsSpeedBoost = true;
		Character->GetCharacterMovement()->MaxWalkSpeed *= SpeedMultiplier;
	}
	
	Super::PickedUpBy_Implementation(Character);
}
