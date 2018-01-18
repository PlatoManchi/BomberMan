// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleBlock.h"
#include "LevelCreator.h"
#include "Gameplay/Pickups/BasePickup.h"
#include "Gameplay/Pickups/CarpetBombPickup.h"
#include "Gameplay/Pickups/MegaBombPickup.h"
#include "Gameplay/Pickups/RemoteBombPickup.h"
#include "Gameplay/Pickups/SprintPickup.h"

// Engine includes
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

TArray<int32> ADestructibleBlock::ProbabilityArray;

ADestructibleBlock::ADestructibleBlock()
{
	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleTemplateClass(TEXT("/Game/Art/VFX/Particles/PS_DestructibleBlockParticle"));
	if (ExplosionParticleTemplateClass.Object != NULL)
	{
		ExplosionParticleTemplate = ExplosionParticleTemplateClass.Object;
	}

	static ConstructorHelpers::FClassFinder<AActor> CarpetBombPickUpTemplateClass(TEXT("/Game/Blueprints/Gameplay/Pickups/BP_CarpetBombPickup"));
	if (CarpetBombPickUpTemplateClass.Class != NULL)
	{
		CarpetBombPickUpClass = CarpetBombPickUpTemplateClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> MegaBombPickUpTemplateClass(TEXT("/Game/Blueprints/Gameplay/Pickups/BP_MegaBombPickup"));
	if (MegaBombPickUpTemplateClass.Class != NULL)
	{
		MegaBombPickUpClass = MegaBombPickUpTemplateClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> RemoteBombPickUpTemplateClass(TEXT("/Game/Blueprints/Gameplay/Pickups/BP_RemoteBombPickup"));
	if (RemoteBombPickUpTemplateClass.Class != NULL)
	{
		RemoteBombPickUpClass = RemoteBombPickUpTemplateClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> SprintPickUpTemplateClass(TEXT("/Game/Blueprints/Gameplay/Pickups/BP_SprintPickup"));
	if (SprintPickUpTemplateClass.Class != NULL)
	{
		SprintPickUpClass = SprintPickUpTemplateClass.Class;
	}

	ProbabilityArray = DefaultProbabilityArray;
}

float ADestructibleBlock::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (ExplosionParticleTemplate)
	{
		FTransform transform = GetActorTransform();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, GetActorTransform(), true);
	}
	
	int32 index = FMath::RandRange(0, ProbabilityArray.Num() - 1);
	int32 pickupType = ProbabilityArray[index];
	ProbabilityArray.RemoveAt(index);

	if (pickupType != 0)
	{
		if (pickupType == 1)
		{
			ABasePickup* pickup = GetWorld()->SpawnActor<ABasePickup>(CarpetBombPickUpClass, GetActorTransform());
		}
		else if (pickupType == 2)
		{
			ABasePickup* pickup = GetWorld()->SpawnActor<ABasePickup>(MegaBombPickUpClass, GetActorTransform());
		}
		else if (pickupType == 3)
		{
			ABasePickup* pickup = GetWorld()->SpawnActor<ABasePickup>(RemoteBombPickUpClass, GetActorTransform());
		}
		else if (pickupType == 4)
		{
			ABasePickup* pickup = GetWorld()->SpawnActor<ABasePickup>(SprintPickUpClass, GetActorTransform());
		}
	}

	// Once the pool is empty refill the pool
	if (ProbabilityArray.Num() == 0)
	{
		ProbabilityArray = DefaultProbabilityArray;
	}

	TActorIterator<ALevelCreator> itr(GetWorld());
	if (itr)
	{
		(*itr)->RecollectDestructibleBlock(this);
	}

	return actualDamage;
}

