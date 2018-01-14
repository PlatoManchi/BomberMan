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

	UPROPERTY(EditDefaultsOnly, Category = "Pickup|CarpedBombPickup")
	int32 IncrementAmount;
};
