// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelCreator.generated.h"

#define _MAP_WIDTH_ 13
#define _MAP_HEIGHT_ 13

class ABaseBlock;

UCLASS()
class BOMBERMAN_API ALevelCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelCreator();

	/** Resets the level to initial conditions
	*/
	void ResetLevel();

	/** Variables to hold the tile height and width
	*/
	const static float TILE_X_LENGTH;
	const static float TILE_Y_LENGTH;
	const static float TILE_Z_LENGTH;

	/** Variables to hold the map size
	*/
	const static int32 MAP_WIDTH;
	const static int32 MAP_HEIGHT;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Template for indestructible blocks
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseBlock> IndestructibleBlockClass;
	
private:
	/** Returns unused indestructible block and removes it from unused array and adds it to used array.
	*	If there are no indestructible blocks in unused array it will spawn a new actor and return the actor.
	*	@return Pointer to Unused indestructible block
	*/
	ABaseBlock* GetIndestructibleBlock();

	/** Used to pool the objects.
	*/
	TArray<ABaseBlock*> UsedIndestructibleBlocksArray, UnusedIndestructibleBlocksArray;

	/** Initial map data
	*/
	int32 MapData[_MAP_HEIGHT_][_MAP_WIDTH_] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
};
