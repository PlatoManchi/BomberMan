// Fill out your copyright notice in the Description page of Project Settings.

#include "RemoteBombPlacerComponent.h"
#include "Characters/BomberManCharacter.h"
#include "Gameplay/RemoteBomb.h"
#include "Gameplay/LevelCreator.h"

// Engine include
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
URemoteBombPlacerComponent::URemoteBombPlacerComponent() :
	Bomb(nullptr),
	MaxPowerupTime(10.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default bomb class
	static ConstructorHelpers::FClassFinder<AActor> BombTypeBPClass(TEXT("/Game/Blueprints/Gameplay/BP_RemoteBomb"));
	if (BombTypeBPClass.Class != NULL)
	{
		BombTypeClass = BombTypeBPClass.Class;
	}

	// Remote bombs will explode after 10 seconds.
	ExplosionDelay = 10.0f;
}


void URemoteBombPlacerComponent::PlaceBomb()
{
	if (!Bomb)
	{
		// If character is already overlapping with a bomb don't place another bomb.
		// This is to avoid multiple bombs in same place
		if (IsOverlappingWithBomb())
			return;
		
		// Place bomb at actor location
		FVector location = OwningCharacter->GetActorLocation();
		location.Z = ALevelCreator::TILE_Z_LENGTH / 2.0f;

		Bomb = GetWorld()->SpawnActor<ABomb>(BombTypeClass, location, FRotator::ZeroRotator);
		Bomb->SetOwningCharacter(OwningCharacter);
		Bomb->SetExplosionLength(ExplosionLength);
		Bomb->SetExplosionDelay(ExplosionDelay);
	}
	else
	{
		Bomb->Explode();
		Bomb = nullptr;
	}
}

void URemoteBombPlacerComponent::SetMaxPowerupTime(float NewMaxPowerupTime)
{
	MaxPowerupTime = NewMaxPowerupTime;
}


// Called every frame
void URemoteBombPlacerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeElapsed += DeltaTime;

	// When time is up change back to normal bomb placer class
	if (TimeElapsed > MaxPowerupTime)
	{
		OwningCharacter->SetBombPlacerClass(UBombPlacerComponent::StaticClass());
	}
}

