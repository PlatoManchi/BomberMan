// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

// Forward decelerations
class ABomberManCharacter;

class UBoxComponent;
class USceneComponent;

UCLASS()
class BOMBERMAN_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties
	*/
	ABasePickup();

protected:
	/** Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;

	/** Called every frame
	*/
	virtual void Tick(float DeltaTime) override;

	/** When the pick up is picked up by character.
	*	@param Character Pointer to the character that picked up this pickup.
	*/
	virtual void PickedUpBy(ABomberManCharacter* Character);

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

	/** Rate at which visual component should rotate. Angle per second
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float VisualRotationRate;
private:	
	/** Angle for rotating the visual component
	*/
	float VisualComponentRotationAngle;

	/** Box component that is used as collider
	*/
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USceneComponent* VisualComponent;
};