// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberManCamera.h"
#include "Characters/BomberManCharacter.h"

// Engine includes
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABomberManCamera::ABomberManCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	// Create a follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ABomberManCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomberManCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageCameraZoom(DeltaTime);
	SetCameraToCharacterMid();
}

void ABomberManCamera::SetCameraToCharacterMid()
{
	int playerCount = 0;
	FVector TotalPositions = FVector::ZeroVector;

	// Loop through all characters and calculate the total
	for (TActorIterator<ABomberManCharacter> itr(GetWorld()); itr; ++itr)
	{
		playerCount++;
		TotalPositions = TotalPositions + (*itr)->GetActorLocation();
	}

	// Set camera in middle of the characters
	if (playerCount > 0)
	{
		// Adding origin as another point, so that camera panning will always favored towards the center of level.
		TotalPositions = TotalPositions + FVector::ZeroVector;
		playerCount++;

		FVector averagePosition = TotalPositions / playerCount;

		SetActorLocation(averagePosition);
	}
	
}

void ABomberManCamera::ManageCameraZoom(float DeltaTime)
{
	float maxDistance = 0;

	for (TActorIterator<ABomberManCharacter> itr1(GetWorld()) ; itr1 ; ++itr1)
	{
		for (TActorIterator<ABomberManCharacter> itr2(GetWorld()); itr2; ++itr2)
		{
			float tmpDistance = FVector::Distance((*itr1)->GetActorLocation(), (*itr2)->GetActorLocation());
			if (tmpDistance > maxDistance)
			{
				maxDistance = tmpDistance;
			}
		}
	}
	// Add some extra distance so that there is always some view ahead of characters instead of characters
	// being on the edge of screen
	maxDistance += 400.0f;
	maxDistance = FMath::Clamp(maxDistance, 600.0f, 2500.0f);
	float newTargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, maxDistance, DeltaTime, 1.0f);

	SpringArmComponent->TargetArmLength = newTargetArmLength;
	
}