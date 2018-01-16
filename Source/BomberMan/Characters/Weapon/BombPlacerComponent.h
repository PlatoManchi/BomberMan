// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BombPlacerComponent.generated.h"

// Forward deceleration
class ABomb;
class ABomberManCharacter;

/** This is like the gun. It will be responsible for placing bombs (like firing bullets).
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API UBombPlacerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBombPlacerComponent();

	/** Set the owner of this component. This is just a function to cache the character.
	*	@param NewOwningCharacter The character that this component is attached to.
	*/
	void SetOwningCharacter(ABomberManCharacter* NewOwningCharacter);

	/** If able to, place the bomb at character's location.
	*/
	virtual void PlaceBomb();

	/** Sets the explosion length.
	*	@param NewExplosionLength New explosion length to set.
	*/
	void SetExplosionLength(int32 NewExplosionLength);

	/** Set the explosion delay.
	*	@param NewExplosionDelay New explosion delay to set.
	*/
	void SetExplosionDelay(float NewExplosionDelay);

	/** Returns the number of blocks the explosion will happen.
	*/
	FORCEINLINE int32 GetExplosionLength() const { return ExplosionLength; }

	/** Returns the delay for each bomb.
	*/
	FORCEINLINE float GetExplosionDelay() const { return ExplosionDelay; }
protected:
	/** Returns true if Owning character is 
	*/
	bool IsOverlappingWithBomb() const;

	/** The character that owns the component.
	*/
	ABomberManCharacter* OwningCharacter;

	/** Number of blocks around the bomb that bomb can effect.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true", MinValue = 1))
	int32 ExplosionLength;

	/** Delay before bomb explodes.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true", MinValue = 0))
	float ExplosionDelay;

	/** Type of bomb this character can place.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABomb> BombTypeClass;

};
