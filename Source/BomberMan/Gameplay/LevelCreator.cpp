// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelCreator.h"
#include "BaseBlock.h"

// Engine includes
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ALevelCreator::ALevelCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComponent;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AActor> IndestructibleBlockBPClass(TEXT("/Game/Blueprints/Gameplay/BP_BaseBlock"));
	if (IndestructibleBlockBPClass.Class != NULL)
	{
		IndestructibleBlockClass = IndestructibleBlockBPClass.Class;
	}
	
}

void ALevelCreator::ResetLevel()
{
	UsedIndestructibleBlocksArray = UsedIndestructibleBlocksArray;
	UsedIndestructibleBlocksArray.Empty();

	/** Creating the initial indestructible blocks that will be there everywhere
	*/
	for (int32 y = 0; y < 13; ++y)
	{
		for (int32 x = 0; x < 13; ++x)
		{
			if (MapData[y][x] == 1)
			{
				FVector location(x * 100 + 50 - 650, y * 100 + 50 - 650, 50);
				ABaseBlock* block = GetIndestructibleBlock();
				block->SetActorLocation(location);
			}
		}
	}
	
}

// Called when the game starts or when spawned
void ALevelCreator::BeginPlay()
{
	Super::BeginPlay();
	
	ResetLevel();

	
}

// Called every frame
void ALevelCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABaseBlock* ALevelCreator::GetIndestructibleBlock()
{
	ABaseBlock* result = nullptr;

	// If there are unused indestructible blocks return one else create new
	if (UnusedIndestructibleBlocksArray.Num() > 0)
	{
		result = UnusedIndestructibleBlocksArray.Pop(false);
	}
	else
	{
		result = GetWorld()->SpawnActor<ABaseBlock>(IndestructibleBlockClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	// Initializing the block
	result->ResetBlock();

	// Pushing the result into the used indestructible block
	UsedIndestructibleBlocksArray.Add(result);
	return result;
}

