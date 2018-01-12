// Fill out your copyright notice in the Description page of Project Settings.

#include "BombPlacerComponent.h"
#include "Characters/BomberManCharacter.h"
#include "Gameplay/Bomb.h"

// Engine includes
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UBombPlacerComponent::UBombPlacerComponent() :
	ExplosionLength(3),
	ExplosionDelay(5)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default bomb class
	static ConstructorHelpers::FClassFinder<AActor> BombTypeBPClass(TEXT("/Game/Blueprints/Gameplay/BP_Bomb"));
	if (BombTypeBPClass.Class != NULL)
	{
		BombTypeClass = BombTypeBPClass.Class;
	}
}


void UBombPlacerComponent::SetOwningCharacter(ABomberManCharacter * NewOwningCharacter)
{
	OwningCharacter = NewOwningCharacter;
}

void UBombPlacerComponent::PlaceBomb()
{
	if (BombTypeClass)
	{
		FVector location = OwningCharacter->GetActorLocation();
		location.Z = 50.0f;
		ABomb* bomb = GetWorld()->SpawnActor<ABomb>(BombTypeClass, location, FRotator::ZeroRotator);
		bomb->SetOwningCharacter(OwningCharacter);
		bomb->ExplosionLength = ExplosionLength;
		bomb->ExplosionDelay = ExplosionDelay;
	}
}

// Called when the game starts
void UBombPlacerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBombPlacerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

