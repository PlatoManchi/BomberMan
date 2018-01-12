// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleBlock.h"
#include "LevelCreator.h"

// Engine includes
#include "EngineUtils.h"



float ADestructibleBlock::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	TActorIterator<ALevelCreator> itr(GetWorld());
	if (itr)
	{
		(*itr)->RecollectDestructibleBlock(this);
	}

	return actualDamage;
}

