// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BombPlacerComponent.h"
#include "RemoteBombPlacerComponent.generated.h"

// Forward decelerations
class ABomb;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API URemoteBombPlacerComponent : public UBombPlacerComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URemoteBombPlacerComponent();

	/** If able to, place the bomb at character's location.
	*/
	virtual void PlaceBomb() override;

	/** Set the amount of time this power up stays
	*/
	void SetMaxPowerupTime(float NewMaxPowerupTime);

protected:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** Save the pointer to bomb placed so that it can be exploded remotely.
	*/
	ABomb* Bomb;

	/** Amount of time elapsed since this component is added to character
	*/
	float TimeElapsed;

	/** Amount of time this remote control bomb power up stays.
	*/
	float MaxPowerupTime;
};
