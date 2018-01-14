// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BomberManGameMode.h"
#include "Camera/BomberManCamera.h"
#include "Characters/BomberManPlayerState.h"

// Engine includes
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"



ABomberManGameMode::ABomberManGameMode()
{
	// Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_BomberManCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Characters/BP_BomberManController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// Set default player state class
	PlayerStateClass = ABomberManPlayerState::StaticClass();
}

void ABomberManGameMode::BeginPlay()
{
	// Creating another player so that there are two players
	UGameplayStatics::CreatePlayer(GetWorld(), 1);

	// Getting the camera from world and setting it as the camera to be used as target to render.
	TActorIterator<ABomberManCamera> itr(GetWorld());
	if (itr)
	{
		ABomberManCamera* bombermanCamera = *itr;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(bombermanCamera);
	}
}

APlayerController * ABomberManGameMode::Login(UPlayer * NewPlayer, ENetRole InRemoteRole, const FString & Portal, const FString & Options, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	APlayerController* controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	if (controller->IsValidLowLevel())
	{
		ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(controller->PlayerState);

		// Initializing the player
		if (playerState)
		{
			// Setting player health
			playerState->MaxPlayerHealth = 1.0f;
			playerState->PlayerHealth = playerState->MaxPlayerHealth;
			
			// Setting the bombs available
			playerState->MaxBombsAvailable = 1;
			playerState->CurrentBombsAvailable = playerState->MaxBombsAvailable;
		}
	}

	return controller;
}
