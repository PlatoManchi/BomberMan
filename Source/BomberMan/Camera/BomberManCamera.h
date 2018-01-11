// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BomberManCamera.generated.h"

// Forward decelerations
class USpringArmComponent;
class UCameraComponent;

/** This class handles the camera panning, moving and everything to do with camera
*/
UCLASS()
class BOMBERMAN_API ABomberManCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	/* Sets default values for this actor's properties
	*/
	ABomberManCamera();

protected:
	/* Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;

	/* Called every frame
	*/
	virtual void Tick(float DeltaTime) override;

private:
	/** Spring component that handles the camera
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	/** Follow camera
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	
};
