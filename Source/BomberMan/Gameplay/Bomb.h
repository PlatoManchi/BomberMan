// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

// Forward decelerations
class ABomberManCharacter;
class ABomb;
class UBombPlacerComponent;
class UBoxComponent;
class USceneComponent;
class ABomberManCharacter;

// Delegate decelerations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBombExploded, ABomb*, Bomb);

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()

	// Giving full access of the bomb to the bomb placer.
	friend class UBombPlacerComponent;

public:	
	// Sets default values for this actor's properties
	ABomb();

	/** Event fires when bomb explodes
	*/
	UPROPERTY(BlueprintAssignable, Category = "Bomb")
	FBombExploded OnBombExploded;
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

	/** Take damage event.
	*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	/** Call back when ever the collider begin overlap with any object.
	*	@param OverlappedComp  Pointer to PrimitiveComponent in this actor that overlapped with something in scene.
	*	@param OtherActor  Pointer to the actor that the OvelappedComp overlapped with in scene.
	*	@param OtherComp  Pointer to the PrimitiveComponent in OtherActor that overlapped with this collider.
	*	@param OtherBodyIndex  Index of the component that is overlapped in the OtherActor.
	*	@param FromSweep  Is the overlap happed due to sweep rotation or position change or not.
	*	@param SweepResult  If the overlapping even is due to sweep, then this will hold the sweep result for that event.
	*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	/** Call back when ever the collider end overlap with any object.
	*	@param OverlappedComp  Pointer to PrimitiveComponent in this actor that end overlap with something in scene.
	*	@param OtherActor  Pointer to the actor that the OvelappedComp end overlap with in scene.
	*	@param OtherComp  Pointer to the PrimitiveComponent in OtherActor that end overlap with this collider.
	*	@param OtherBodyIndex  Index of the component that is end overlap in the OtherActor.
	*/
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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

	/** If true then this bomb is exploding so as to avoid infinite nested explosion.
		If Explode is called then it will deal damage to adjacent bomb which will explode and damage this bomb, and this bomb
		will again explode and damage same adjacent bomb causing infinite loop.

		To avoid this nested infinite calls, if bomb exploded, if true then dont process any damage or explosion requestss.
	*/
	bool IsExploding;
	
	/** If bomb is spawned on player then bomb will displace player or player can get stuck inside bomb.
		To avoid this, spawn bomb with overlap if there are no players overlapping with bomb then make it block all
	*/
	int32 PlayerCountOverlappingBomb;

	/** Do a multi line trace and return the location
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

	/** The character that places this bomb on map.
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
