// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BomberManController.generated.h"

/**
 * 
 */

// Forward declarations
class ABomberManCharacter;

UCLASS()
class BOMBERMAN_API ABomberManController : public APlayerController
{
	GENERATED_BODY()

public:

protected:
	/** Called after controller successfully posses a pawn.
	*	@param InPawn Pointer to the pawn that this controller will posses
	*/
	virtual void SetPawn(APawn* InPawn) override;

	/** AController interface
	*/
	virtual void SetupInputComponent() override;

	/** Called for forwards/backward input 
	*	@param Value The value representing input in vertical axis
	*/
	void MoveForward(float Value);

	/** Called for side to side input 
	*	@param Value The value representing input in horizontal axis
	*/
	void MoveRight(float Value);

	/** If able to, place the bomb at player's position.
	*/
	void PlaceBomb();

	// Caching the character
	ABomberManCharacter* BomberManCharacter;

private:

};
