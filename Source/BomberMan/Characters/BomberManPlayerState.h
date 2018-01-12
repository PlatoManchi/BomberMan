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
	/** Holds Player's current health
	*/
	float PlayerHealth;

	/** Holds Player's max health
	*/
	float MaxPlayerHealth;
};
