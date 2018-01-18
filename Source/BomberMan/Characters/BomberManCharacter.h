// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BomberManCharacter.generated.h"

// Forward decelerations
class ABomberManController;
class ABomb;
class UBombPlacerComponent;
class USkeletalMesh;
// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam (FRemoteBombPickup, float, MaxTime);

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

	/** Change the bomb placer component.
	*	@param NewBombPlacer Class of new bomb placer.
	*/
	UBombPlacerComponent* SetBombPlacerClass(TSubclassOf<UBombPlacerComponent> NewBombPlacer);

	/** Resets character
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "BomberManCharacter")
	void Reset();

	/** Return the bomb placer component that this character uses.
	*/
	FORCEINLINE UBombPlacerComponent* GetBombPlacerComponent() const { return BombPlacer; }

	/** Event that will be fired when remote bomb pickup is picked.
	*/
	UPROPERTY(BlueprintAssignable, Category = "BomberManCharacter")
	FRemoteBombPickup OnRemoteBombPickup;
protected:
	/** Called at the start of the game.
	*/
	virtual void BeginPlay() override;

	/** Called when this Pawn is possessed.
	*	@param NewController The controller possessing this pawn
	*/
	virtual void PossessedBy(AController* NewController) override;

	/** Take damage event.
	*	@param	DamageAmount How much damage to apply
	*	@param	DamageEvent Data package that fully describes the damage received.
	*	@param	EventInstigator The Controller responsible for the damage.
	*	@param	DamageCauser The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	UFUNCTION(BlueprintNativeEvent, Category = "BomberManCharacter")
	void PlayerDead(FVector Force);

private:
	/** Cache the initial walk speed so that it can be used while resetting the character
	*/
	float InitWalkSpeed;
	
	/** Bomb placer that acts like gun and is responsible to place the bombs
	*/
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UBombPlacerComponent* BombPlacer;
};

