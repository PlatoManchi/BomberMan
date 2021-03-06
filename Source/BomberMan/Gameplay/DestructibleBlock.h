// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/BaseBlock.h"
#include "DestructibleBlock.generated.h"

class ABaseBlock;
class ACarpetBombPickup;
class AMegaBombPickup;
class ARemoteBombPickup;
class ASprintPickup;

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
	UPROPERTY(EditDefaultsOnly, Category = "Block|DestructibleBlock")
	UParticleSystem* ExplosionParticleTemplate;

	/** Probabilities of drops. Creating a pseudo random pool so that probability always works.
	*	Instead of relaying on random and hoping that it works.
	*	To get 30% drop rate, out of 30 sample set 9 times has to be positive hit.
	*	So create a pool of 30 sample set and have 9 positive outputs.
	*	0 - no drop
	*	1 - Carpet bomb pick up
	*	2 - Mega bomb pick up
	*	3 - Remote bomb pick up
	*	4 - Sprint pick up
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Block|DestructibleBlock")
	TArray<int32> DefaultProbabilityArray = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 1, 1, 2, 2, 3, 3, 4, 4, 1};
	
	/** Probabilities to be used. The pool has to be single pool for all blocks. So make it static.
	*/
	static TArray<int32> ProbabilityArray;

	/** Carpet bomb class
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Block|DestructibleBlock")
	TSubclassOf<ACarpetBombPickup> CarpetBombPickUpClass;

	/** Mega bomb class
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Block|DestructibleBlock")
	TSubclassOf<AMegaBombPickup> MegaBombPickUpClass;

	/** Remote bomb class
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Block|DestructibleBlock")
	TSubclassOf<ARemoteBombPickup> RemoteBombPickUpClass;

	/** Sprint class
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Block|DestructibleBlock")
	TSubclassOf<ASprintPickup> SprintPickUpClass;
};

