// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BomberManGameMode.h"
#include "Camera/BomberManCamera.h"
#include "Characters/BomberManPlayerState.h"
#include "Characters/BomberManCharacter.h"
#include "UI/InGameHUDWidget.h"

// Engine includes
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"



ABomberManGameMode::ABomberManGameMode() :
	InGameHUD(nullptr)
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

	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<UUserWidget> InGameHUDBPClass(TEXT("/Game/Blueprints/UI/InGameHUD/WBP_InGameHUDWidget"));
	if (InGameHUDBPClass.Class != NULL)
	{
		InGameHUDClass = InGameHUDBPClass.Class;
	}
	
	InGameHUD = CreateWidget<UInGameHUDWidget>(GetWorld(), InGameHUDClass);
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

	InGameHUD->AddToViewport();
}


void ABomberManGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer && InGameHUD)
	{
		ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(NewPlayer->PlayerState);
		ABomberManCharacter* character = Cast<ABomberManCharacter>(NewPlayer->GetPawn());
		
		// Initializing the player
		if (playerState)
		{
			playerState->PlayerID = UGameplayStatics::GetPlayerControllerID(NewPlayer);
			
			// Setting player health
			playerState->MaxPlayerHealth = 1.0f;
			playerState->PlayerHealth = playerState->MaxPlayerHealth;

			// Setting the bombs available
			playerState->MaxBombsAvailable = 1;
			playerState->CurrentBombsAvailable = playerState->MaxBombsAvailable;

			// Speed boost
			playerState->IsSpeedBoost = false;

			// Setting up UI.
			if (character)
			{
				if (playerState->PlayerID == 0)
				{
					InGameHUD->SetPlayer1(character);
				}

				if (playerState->PlayerID == 1)
				{
					InGameHUD->SetPlayer2(character);
				}
			}
		}
	}
}
