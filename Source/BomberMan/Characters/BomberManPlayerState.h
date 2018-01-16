// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BomberManPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABomberManPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	/** Default constructor
	*/
	ABomberManPlayerState();

	/** ID of the player
	*/
	int32 PlayerID;

	/** Holds Player's current health
	*/
	float PlayerHealth;

	/** Holds Player's max health
	*/
	float MaxPlayerHealth;

	/** How many bombs currently available that player can place on map
	*/
	int32 CurrentBombsAvailable;

	/** Max bombs that player is allowed to place on map at once.
	*/
	int32 MaxBombsAvailable;

	/** True if player took speed boost and speed is boosted
	*/
	bool IsSpeedBoost;
};
