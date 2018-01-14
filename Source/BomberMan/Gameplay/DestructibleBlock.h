// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/BaseBlock.h"
#include "DestructibleBlock.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ADestructibleBlock : public ABaseBlock
{
	GENERATED_BODY()
	
public:
	/** Default constructor
	*/
	ADestructibleBlock();

protected:
	/** Take damage event.
	*	@param	DamageAmount How much damage to apply
	*	@param	DamageEvent Data package that fully describes the damage received.
	*	@param	EventInstigator The Controller responsible for the damage.
	*	@param	DamageCauser The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Particle to play when explosion happens
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	UParticleSystem* ExplosionParticleTemplate;
};
