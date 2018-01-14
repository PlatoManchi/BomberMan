// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleBlock.h"
#include "LevelCreator.h"

// Engine includes
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"


ADestructibleBlock::ADestructibleBlock()
{
	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleTemplateClass(TEXT("/Game/Art/VFX/Particles/PS_DestructibleBlockParticle"));
	if (ExplosionParticleTemplateClass.Object != NULL)
	{
		ExplosionParticleTemplate = ExplosionParticleTemplateClass.Object;
	}
}

float ADestructibleBlock::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (ExplosionParticleTemplate)
	{
		FTransform transform = GetActorTransform();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, GetActorTransform(), true);
	}
	
	TActorIterator<ALevelCreator> itr(GetWorld());
	if (itr)
	{
		(*itr)->RecollectDestructibleBlock(this);
	}

	return actualDamage;
}

