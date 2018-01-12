// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

// Forward decelerations
class UBombPlacerComponent;
class UBoxComponent;
class USceneComponent;
class ABomberManCharacter;

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()

	// Giving full access of the bomb to the bomb placer.
	friend class UBombPlacerComponent;

public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called every frame
	*	@param DeltaTime Time elapsed since last frame
	*/
	virtual void Tick(float DeltaTime) override;

	/** Called to explode the bomb
	*/
	virtual void Explode();

	/** Set the owner of this component. This is just a function to cache the character.
	*	@param NewOwningCharacter The character that this component is attached to.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Bomb")
	void SetOwningCharacter(ABomberManCharacter* NewOwningCharacter);

	/** Particle to play when explosion happens
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* ExplosionParticleTemplate;
	
private:
	/** Check for all the actors in the explosion area and damage them
	*/
	void DealDamage();

	/** Do a multipline line trace and return the location
	*	@return returns the location of the line trace
	*/
	FVector GetLineTraceLocation(FVector Start, FVector End);

	/** Number of blocks around the bomb that bomb can effect.
	*/
	int32 ExplosionLength;

	/** Amount of time to delay before exploding
	*/
	float ExplosionDelay;

	/** Amount of time elapsed since the bomb spawned.
	*/
	float TimeElapsed;

	/** Distances in all directions
	*/
	float leftDistance, rightDistance, upDistance, downDistance;
	/** The character that owns the component.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Bomb", meta = (AllowPrivateAccess = "true"))
	ABomberManCharacter* OwningCharacter;

	/** Collider that will take care of collisions.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;

	/** Colliders damaging after explosion
	*/
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* HorizontalBoxCollider;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* VerticalBoxCollider;

};
