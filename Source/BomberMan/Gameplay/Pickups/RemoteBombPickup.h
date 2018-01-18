// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Pickups/BasePickup.h"
#include "RemoteBombPickup.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ARemoteBombPickup : public ABasePickup
{
	GENERATED_BODY()
public:
	/** Default constructor
	*/
	ARemoteBombPickup();

protected:

	/** Called when this pick up is picked by player.
	*/
	virtual void PickedUpBy_Implementation(ABomberManCharacter* Character) override;
	
	/** Amount of time this pick up works
	*/
	UPROPERTY(EditDefaultsOnly, Category = "BombPlacer", meta = (MinValue = 0))
	float MaxPowerupTime;
};
