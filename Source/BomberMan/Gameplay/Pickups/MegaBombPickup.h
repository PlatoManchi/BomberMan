// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Pickups/BasePickup.h"
#include "MegaBombPickup.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AMegaBombPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	/** Default constructor
	*/
	AMegaBombPickup();
protected:

	/** Called when this pick up is picked by player.
	*/
	virtual void PickedUpBy_Implementation(ABomberManCharacter* Character) override;
	
private:
	/** Number of extra tiles to add to explosion
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Pickup|MegaBombPickup", meta = (MinValue = 0))
	int32 IncrementAmount;
};
