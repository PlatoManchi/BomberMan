// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BomberManCharacter.generated.h"

// Forward decelerations
class ABomberManController;
class ABomb;
class UBombPlacerComponent;

UCLASS(config=Game)
class ABomberManCharacter : public ACharacter
{
	GENERATED_BODY()

	// Giving full access of character to controller.
	friend class ABomberManController;
	friend class ABomb;

public:
	/** Default constructor
	*/
	ABomberManCharacter();

	/** Return the bomb placer component that this character uses.
	*/
	FORCEINLINE UBombPlacerComponent* GetBombPlacerComponent() const { return BombPlacer; }
protected:
	/** Called when this Pawn is possessed.
	*	@param NewController The controller possessing this pawn
	*/
	virtual void PossessedBy(AController* NewController) override;

	/** Take damage event.
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	/** Called for forwards/backward input 
	*	@param Value The value representing input in vertical axis
	*/
	void MoveForward(float Value);

	/** Called for side to side input 
	*	@param Value The value representing input in horizontal axis
	*/
	void MoveRight(float Value);

	/** If able to, place the bomb at character's location.
	*/
	void PlaceBomb();

	/** Set the visuals for player based on the ID
	*	@param id Id of player.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "BomberManCharacter")
	void SetPlayerID(int32 id);

	/** Event fired when bomb that this character placed explodes
	*/
	UFUNCTION()
	void OnBombExploded(ABomb* Bomb);
private:
	/** Bomb placer that acts like gun and is responsible to place the bombs
	*/
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UBombPlacerComponent* BombPlacer;
};

