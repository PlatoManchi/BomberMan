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
	
protected:
	/** Take damage event.
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
};
