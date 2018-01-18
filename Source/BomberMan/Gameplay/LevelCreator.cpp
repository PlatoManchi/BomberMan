// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelCreator.h"
#include "BaseBlock.h"

// Engine includes
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

const float ALevelCreator::TILE_X_LENGTH = 100.0f;
const float ALevelCreator::TILE_Y_LENGTH = 100.0f;
const float ALevelCreator::TILE_Z_LENGTH = 100.0f;

const int32 ALevelCreator::MAP_WIDTH = _MAP_WIDTH_;
const int32 ALevelCreator::MAP_HEIGHT = _MAP_HEIGHT_;
// Sets default values
ALevelCreator::ALevelCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComponent;

	// set default pawn class to our indestructible block
	static ConstructorHelpers::FClassFinder<AActor> IndestructibleBlockBPClass(TEXT("/Game/Blueprints/Gameplay/BP_BaseBlock"));
	if (IndestructibleBlockBPClass.Class != NULL)
	{
		IndestructibleBlockClass = IndestructibleBlockBPClass.Class;
	}
	
	// set default pawn class to our destructible block
	static ConstructorHelpers::FClassFinder<AActor> DestructibleBlockBPClass(TEXT("/Game/Blueprints/Gameplay/BP_DestructibleBlock"));
	if (DestructibleBlockBPClass.Class != NULL)
	{
		DestructibleBlockClass = DestructibleBlockBPClass.Class;
	}
}

void ALevelCreator::ResetLevel()
{
	UnusedIndestructibleBlocksArray.Append(UsedIndestructibleBlocksArray);
	UsedIndestructibleBlocksArray.Empty();

	UnusedDestructibleBlocksArray.Append(UsedDestructibleBlocksArray);
	UsedDestructibleBlocksArray.Empty();

	PopulateMapData();

	/** Creating the initial indestructible blocks that will be there everywhere
	*/
	for (int32 y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int32 x = 0; x < MAP_WIDTH; ++x)
		{
			// Offset location by LevelCreator location so that level is always made around LevelCreator location
			// instead of being made 
			FVector location(x * TILE_X_LENGTH + TILE_X_LENGTH / 2.0f - TILE_X_LENGTH * MAP_WIDTH / 2.0f, y * TILE_Y_LENGTH + TILE_Y_LENGTH / 2.0f - TILE_Y_LENGTH * MAP_HEIGHT / 2.0f, TILE_Z_LENGTH / 2.0f);
			location = location + GetActorLocation();

			if (MapData[y][x] == 1)
			{
				ABaseBlock* block = GetIndestructibleBlock();
				block->SetActorLocation(location);
			}
			else if (MapData[y][x] == 2)
			{
				ABaseBlock* block = GetDestructibleBlock();
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

		// Weld the actor to LevelCreator so that if LevelCreator is moved, the whole level will move.
		result->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true));
	}

	// Initializing the block
	result->ResetBlock();

	// Pushing the result into the used indestructible block
	UsedIndestructibleBlocksArray.Add(result);
	return result;
}

ABaseBlock * ALevelCreator::GetDestructibleBlock()
{
	ABaseBlock* result = nullptr;

	// If there are unused indestructible blocks return one else create new
	if (UnusedDestructibleBlocksArray.Num() > 0)
	{
		result = UnusedDestructibleBlocksArray.Pop(false);
	}
	else
	{
		result = GetWorld()->SpawnActor<ABaseBlock>(DestructibleBlockClass, FVector::ZeroVector, FRotator::ZeroRotator);

		// Weld the actor to LevelCreator so that if LevelCreator is moved, the whole level will move.
		result->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true));
	}

	// Initializing the block
	result->ResetBlock();

	// Pushing the result into the used indestructible block
	UsedDestructibleBlocksArray.Add(result);
	return result;
}

void ALevelCreator::PopulateMapData()
{
	ProbabilityArray = DefaultProbabilityArray;

	for (int32 y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int32 x = 0; x < MAP_WIDTH; ++x)
		{
			if (y % 2 != 0 && x % 2 != 0)
			{
				MapData[y][x] = 1;
			}
			else
			{
				// Spawn the destructible blocks based on the probability pool
				int32 index = FMath::RandRange(0, ProbabilityArray.Num() - 1);
				MapData[y][x] = ProbabilityArray[index];
				ProbabilityArray.RemoveAt(index);
				if (ProbabilityArray.Num() == 0)
				{
					ProbabilityArray = DefaultProbabilityArray;
				}
			}
		}
	}

	// Clearing the spawn points.
	// Top left
	MapData[0][0] = MapData[0][1] = MapData[1][0] = MapData[2][0] = MapData[2][1] = 0;
	// Top right
	MapData[0][MAP_WIDTH - 1] = MapData[0][MAP_WIDTH - 2] = MapData[1][MAP_WIDTH - 1] = MapData[2][MAP_WIDTH - 1] = MapData[2][MAP_WIDTH - 2] = 0;
	// Bottom left
	MapData[MAP_HEIGHT - 1][0] = MapData[MAP_HEIGHT - 1][1] = MapData[MAP_HEIGHT - 2][0] = MapData[MAP_HEIGHT - 3][0] = MapData[MAP_HEIGHT - 3][1] = 0;
	// Bottom right
	MapData[MAP_HEIGHT - 1][MAP_WIDTH - 1] = MapData[MAP_HEIGHT - 1][MAP_WIDTH - 2] = MapData[MAP_HEIGHT - 2][MAP_WIDTH - 1] = MapData[MAP_HEIGHT - 3][MAP_WIDTH - 1] = MapData[MAP_HEIGHT - 3][MAP_WIDTH - 2] = 0;
}

void ALevelCreator::RecollectDestructibleBlock(ABaseBlock* Block)
{
	Block->SetActorLocation(FVector(0, 0, 10000));
	UsedDestructibleBlocksArray.Remove(Block);
	UnusedDestructibleBlocksArray.Add(Block);
}

