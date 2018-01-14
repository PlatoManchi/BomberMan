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
	/** Default ocnstructor
	*/
	AMegaBombPickup();

	/** Number of extra tiles to add to explosion
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Pickup|MegaBombPickup")
	int32 IncrementCount;

protected:

	virtual void PickedUpBy(ABomberManCharacter* Character) override;
	
};
