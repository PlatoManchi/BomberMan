// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BomberManCharacter.h"
#include "BomberManPlayerState.h"
#include "BomberManGameMode.h"
#include "Gameplay/Bomb.h"
#include "Weapon/BombPlacerComponent.h"

// Engine includes
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Animation/SkeletalMeshActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

//////////////////////////////////////////////////////////////////////////
// ABomberManCharacter

ABomberManCharacter::ABomberManCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Creating bomb placer
	BombPlacer = CreateDefaultSubobject<UBombPlacerComponent>(TEXT("BombPlacer"));
	BombPlacer->SetupAttachment(RootComponent);
	BombPlacer->SetOwningCharacter(this);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ABomberManCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

UBombPlacerComponent* ABomberManCharacter::SetBombPlacerClass(TSubclassOf<UBombPlacerComponent> NewBombPlacer)
{
	int32 ExplosionLength = BombPlacer->GetExplosionLength();

	// Destroy previous bomb placer
	BombPlacer->DestroyComponent();

	// Create the new bomb placer type
	BombPlacer = NewObject<UBombPlacerComponent>(this, NewBombPlacer);
	BombPlacer->RegisterComponent();
	BombPlacer->SetOwningCharacter(this);

	// Setting the values.
	BombPlacer->SetExplosionLength(ExplosionLength);

	return BombPlacer;
}

void ABomberManCharacter::PossessedBy(AController * NewController)
{
	// Set character color based on the controller id.
	APlayerController* playerController = Cast<APlayerController>(NewController);
	if (playerController)
	{
		int32 id = UGameplayStatics::GetPlayerControllerID(playerController);

		// Loop through all materials, create dynamic material instance and set the color.
		for (int32 i = 0; i < GetMesh()->GetNumMaterials(); ++i)
		{
			UMaterialInterface* materialInterface = GetMesh()->GetMaterials()[i];
			UMaterialInstanceDynamic* dynMaterial = UMaterialInstanceDynamic::Create(materialInterface, this);

			if (id == 0)
			{
				dynMaterial->SetVectorParameterValue("BodyColor", FLinearColor::Blue);
			}
			else if (id == 1)
			{
				dynMaterial->SetVectorParameterValue("BodyColor", FLinearColor::Red);
			}

			GetMesh()->SetMaterial(i, dynMaterial);
		}

		SetPlayerID(id);
	}
}

float ABomberManCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ABomberManGameMode* gamemode = Cast<ABomberManGameMode>(GetWorld()->GetAuthGameMode());
	ABomberManPlayerState* playerstate = Cast<ABomberManPlayerState>(Controller->PlayerState);

	if (gamemode)
	{
		gamemode->PlayerDead(playerstate->PlayerID);
	}

	GetCharacterMovement()->SetActive(false);

	// Make character ragdoll and apply impulse in opposite direction of the bomb
	FVector direction = GetActorLocation() - DamageCauser->GetActorLocation();
	float distance = direction.Size();
	direction = direction / distance;

	float force = FMath::Lerp(50000, 5000, distance / 500.0f);
	PlayerDead(direction * force);

	return actualDamage;
}

void ABomberManCharacter::PlayerDead_Implementation(FVector Force)
{
	GetMesh()->SetVisibility(false);
}

void ABomberManCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABomberManCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABomberManCharacter::PlaceBomb()
{
	if (BombPlacer)
	{
		BombPlacer->PlaceBomb();
	}
}

void ABomberManCharacter::OnBombExploded(ABomb* Bomb)
{
	ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(Controller->PlayerState);

	if (playerState)
	{
		// Since bomb exploded increment the available bombs
		playerState->CurrentBombsAvailable++;

		// Clamp the available bombs to max bombs.
		if (playerState->CurrentBombsAvailable > playerState->MaxBombsAvailable)
		{
			playerState->CurrentBombsAvailable = playerState->MaxBombsAvailable;
		}
	}
}

void ABomberManCharacter::Reset_Implementation()
{
	GetMesh()->SetVisibility(true);
	GetCharacterMovement()->SetActive(true);
	GetCharacterMovement()->MaxWalkSpeed = InitWalkSpeed;

	SetBombPlacerClass(UBombPlacerComponent::StaticClass());
}