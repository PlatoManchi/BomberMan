// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Pickups/BasePickup.h"
#include "SprintPickup.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ASprintPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	/** Default constructor
	*/
	ASprintPickup();

protected:
	/** Called when this pick up is picked by player.
	*/
	virtual void PickedUpBy_Implementation(ABomberManCharacter* Character) override;

private:
	/** Factor at which 
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Pickup|SprintPickup")
	float SpeedMultiplier;
};
