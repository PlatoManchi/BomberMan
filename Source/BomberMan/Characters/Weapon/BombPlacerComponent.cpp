// Fill out your copyright notice in the Description page of Project Settings.

#include "BombPlacerComponent.h"
#include "Characters/BomberManCharacter.h"
#include "Characters/BomberManPlayerState.h"
#include "Gameplay/Bomb.h"
#include "Gameplay/LevelCreator.h"

// Engine includes
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

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
		ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(OwningCharacter->GetController()->PlayerState);
		
		// Check if player can place bombs
		if (playerState && playerState->CurrentBombsAvailable > 0)
		{
			// Decrementing the available bombs
			playerState->CurrentBombsAvailable--;

			TArray<AActor*> OverlappingActors;
			OwningCharacter->GetCapsuleComponent()->GetOverlappingActors(OverlappingActors);

			bool isOverlappingWithBomb = false;

			for (AActor* actor : OverlappingActors)
			{
				ABomb* bomb = Cast<ABomb>(actor);;
				if (bomb)
				{
					isOverlappingWithBomb = true;
					break;
				}
			}

			// If character is already overlapping with a bomb don't place another bomb.
			// This is to avoid multiple bombs in same place
			if (isOverlappingWithBomb)
				return;

			FVector location = OwningCharacter->GetActorLocation();
			location.Z = ALevelCreator::TILE_Z_LENGTH / 2.0f;
			ABomb* bomb = GetWorld()->SpawnActor<ABomb>(BombTypeClass, location, FRotator::ZeroRotator);
			bomb->SetOwningCharacter(OwningCharacter);
			bomb->ExplosionLength = ExplosionLength;
			bomb->ExplosionDelay = ExplosionDelay;
		}
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

