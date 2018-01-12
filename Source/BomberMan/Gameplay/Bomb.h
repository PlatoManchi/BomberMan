// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

// Forward decelerations
class UBombPlacerComponent;
class UBoxComponent;
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

	/** Call back when ever the collider begin overlap with any object.
	*	@param OverlappedComp  Pointer to PrimitiveComponent in this actor that overlapped with something in scene.
	*	@param OtherActor  Pointer to the actor that the OvelappedComp overlapped with in scene.
	*	@param OtherComp  Pointer to the PrimitiveComponent in OtherActor that overlapped with this collider.
	*	@param OtherBodyIndex  Index of the component that is overlapped in the OtherActor.
	*	@param FromSweep  Is the overlap happed due to sweep rotation or position change or not.
	*	@param SweepResult  If the overlapping even is due to sweep, then this will hold the sweep result for that event.
	*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	*/
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Particle to play when explosion happens
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* ExplosionParticleTemplate;

	/** Collider that will take care of collisions.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UBoxComponent* BoxCollider;
private:
	/** Number of blocks around the bomb that bomb can effect.
	*/
	int32 ExplosionLength;

	/** Amount of time to delay before exploding
	*/
	float ExplosionDelay;

	/** Amount of time elapsed since the bomb spawned.
	*/
	float TimeElapsed;

	/** The character that owns the component.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Bomb", meta = (AllowPrivateAccess = "true"))
	ABomberManCharacter* OwningCharacter;
};
