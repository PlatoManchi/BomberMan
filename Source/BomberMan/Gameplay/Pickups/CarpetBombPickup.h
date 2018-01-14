// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Pickups/BasePickup.h"
#include "CarpetBombPickup.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ACarpetBombPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	/** Default constructor
	*/
	ACarpetBombPickup();
	
protected:
	/** Called when this pick up is picked by player.
	*/
	virtual void PickedUpBy(ABomberManCharacter* Character) override;

private:

	/** Number of extra bombs that will be available for player.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Pickup|CarpedBombPickup", meta = (MinValue = 0))
	int32 IncrementAmount;
};
